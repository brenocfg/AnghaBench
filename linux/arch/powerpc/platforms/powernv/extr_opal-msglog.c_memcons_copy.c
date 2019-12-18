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
typedef  int uint32_t ;
struct memcons {int /*<<< orphan*/  obuf_size; int /*<<< orphan*/  obuf_phys; int /*<<< orphan*/  out_pos; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int MEMCONS_OUT_POS_MASK ; 
 int MEMCONS_OUT_POS_WRAP ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 size_t memory_read_from_buffer (char*,size_t,int /*<<< orphan*/ *,char const*,int) ; 
 char* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

ssize_t memcons_copy(struct memcons *mc, char *to, loff_t pos, size_t count)
{
	const char *conbuf;
	ssize_t ret;
	size_t first_read = 0;
	uint32_t out_pos, avail;

	if (!mc)
		return -ENODEV;

	out_pos = be32_to_cpu(READ_ONCE(mc->out_pos));

	/* Now we've read out_pos, put a barrier in before reading the new
	 * data it points to in conbuf. */
	smp_rmb();

	conbuf = phys_to_virt(be64_to_cpu(mc->obuf_phys));

	/* When the buffer has wrapped, read from the out_pos marker to the end
	 * of the buffer, and then read the remaining data as in the un-wrapped
	 * case. */
	if (out_pos & MEMCONS_OUT_POS_WRAP) {

		out_pos &= MEMCONS_OUT_POS_MASK;
		avail = be32_to_cpu(mc->obuf_size) - out_pos;

		ret = memory_read_from_buffer(to, count, &pos,
				conbuf + out_pos, avail);

		if (ret < 0)
			goto out;

		first_read = ret;
		to += first_read;
		count -= first_read;
		pos -= avail;

		if (count <= 0)
			goto out;
	}

	/* Sanity check. The firmware should not do this to us. */
	if (out_pos > be32_to_cpu(mc->obuf_size)) {
		pr_err("OPAL: memory console corruption. Aborting read.\n");
		return -EINVAL;
	}

	ret = memory_read_from_buffer(to, count, &pos, conbuf, out_pos);

	if (ret < 0)
		goto out;

	ret += first_read;
out:
	return ret;
}