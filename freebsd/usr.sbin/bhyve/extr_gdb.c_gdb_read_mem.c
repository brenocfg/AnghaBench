#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int const uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  append_byte (int const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  cur_vcpu ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  finish_packet () ; 
 int getpagesize () ; 
 int guest_vaddr2paddr (int /*<<< orphan*/ ,int,int*) ; 
 int* memchr (int const*,char,size_t) ; 
 int* paddr_guest2host (int /*<<< orphan*/ ,int,size_t) ; 
 void* parse_integer (int const*,size_t) ; 
 int read_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,size_t) ; 
 int /*<<< orphan*/  send_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_packet () ; 

__attribute__((used)) static void
gdb_read_mem(const uint8_t *data, size_t len)
{
	uint64_t gpa, gva, val;
	uint8_t *cp;
	size_t resid, todo, bytes;
	bool started;
	int error;

	/* Skip 'm' */
	data += 1;
	len -= 1;

	/* Parse and consume address. */
	cp = memchr(data, ',', len);
	if (cp == NULL || cp == data) {
		send_error(EINVAL);
		return;
	}
	gva = parse_integer(data, cp - data);
	len -= (cp - data) + 1;
	data += (cp - data) + 1;

	/* Parse length. */
	resid = parse_integer(data, len);

	started = false;
	while (resid > 0) {
		error = guest_vaddr2paddr(cur_vcpu, gva, &gpa);
		if (error == -1) {
			if (started)
				finish_packet();
			else
				send_error(errno);
			return;
		}
		if (error == 0) {
			if (started)
				finish_packet();
			else
				send_error(EFAULT);
			return;
		}

		/* Read bytes from current page. */
		todo = getpagesize() - gpa % getpagesize();
		if (todo > resid)
			todo = resid;

		cp = paddr_guest2host(ctx, gpa, todo);
		if (cp != NULL) {
			/*
			 * If this page is guest RAM, read it a byte
			 * at a time.
			 */
			if (!started) {
				start_packet();
				started = true;
			}
			while (todo > 0) {
				append_byte(*cp);
				cp++;
				gpa++;
				gva++;
				resid--;
				todo--;
			}
		} else {
			/*
			 * If this page isn't guest RAM, try to handle
			 * it via MMIO.  For MMIO requests, use
			 * aligned reads of words when possible.
			 */
			while (todo > 0) {
				if (gpa & 1 || todo == 1)
					bytes = 1;
				else if (gpa & 2 || todo == 2)
					bytes = 2;
				else
					bytes = 4;
				error = read_mem(ctx, cur_vcpu, gpa, &val,
				    bytes);
				if (error == 0) {
					if (!started) {
						start_packet();
						started = true;
					}
					gpa += bytes;
					gva += bytes;
					resid -= bytes;
					todo -= bytes;
					while (bytes > 0) {
						append_byte(val);
						val >>= 8;
						bytes--;
					}
				} else {
					if (started)
						finish_packet();
					else
						send_error(EFAULT);
					return;
				}
			}
		}
		assert(resid == 0 || gpa % getpagesize() == 0);
	}
	if (!started)
		start_packet();
	finish_packet();
}