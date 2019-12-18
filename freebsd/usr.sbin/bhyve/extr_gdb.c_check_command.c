#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {size_t len; size_t start; char* data; } ;

/* Variables and functions */
 TYPE_1__ cur_comm ; 
 TYPE_1__ cur_resp ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  gdb_suspend_vcpus () ; 
 int /*<<< orphan*/  handle_command (int*,int) ; 
 int /*<<< orphan*/  io_buffer_advance (TYPE_1__*,int) ; 
 int /*<<< orphan*/  io_buffer_consume (TYPE_1__*,int) ; 
 int* io_buffer_head (TYPE_1__*) ; 
 int /*<<< orphan*/  io_buffer_reset (TYPE_1__*) ; 
 int* memchr (int*,char,size_t) ; 
 int parse_byte (int*) ; 
 int /*<<< orphan*/  report_stop () ; 
 int /*<<< orphan*/  response_pending () ; 
 int /*<<< orphan*/  send_char (char) ; 
 int /*<<< orphan*/  send_pending_data (int) ; 
 int stop_pending ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
check_command(int fd)
{
	uint8_t *head, *hash, *p, sum;
	size_t avail, plen;

	for (;;) {
		avail = cur_comm.len;
		if (avail == 0)
			return;
		head = io_buffer_head(&cur_comm);
		switch (*head) {
		case 0x03:
			debug("<- Ctrl-C\n");
			io_buffer_consume(&cur_comm, 1);

			gdb_suspend_vcpus();
			break;
		case '+':
			/* ACK of previous response. */
			debug("<- +\n");
			if (response_pending())
				io_buffer_reset(&cur_resp);
			io_buffer_consume(&cur_comm, 1);
			if (stop_pending) {
				stop_pending = false;
				report_stop();
				send_pending_data(fd);
			}
			break;
		case '-':
			/* NACK of previous response. */
			debug("<- -\n");
			if (response_pending()) {
				cur_resp.len += cur_resp.start;
				cur_resp.start = 0;
				if (cur_resp.data[0] == '+')
					io_buffer_advance(&cur_resp, 1);
				debug("-> %.*s\n", (int)cur_resp.len,
				    io_buffer_head(&cur_resp));
			}
			io_buffer_consume(&cur_comm, 1);
			send_pending_data(fd);
			break;
		case '$':
			/* Packet. */

			if (response_pending()) {
				warnx("New GDB command while response in "
				    "progress");
				io_buffer_reset(&cur_resp);
			}

			/* Is packet complete? */
			hash = memchr(head, '#', avail);
			if (hash == NULL)
				return;
			plen = (hash - head + 1) + 2;
			if (avail < plen)
				return;
			debug("<- %.*s\n", (int)plen, head);

			/* Verify checksum. */
			for (sum = 0, p = head + 1; p < hash; p++)
				sum += *p;
			if (sum != parse_byte(hash + 1)) {
				io_buffer_consume(&cur_comm, plen);
				debug("-> -\n");
				send_char('-');
				send_pending_data(fd);
				break;
			}
			send_char('+');

			handle_command(head + 1, hash - (head + 1));
			io_buffer_consume(&cur_comm, plen);
			if (!response_pending())
				debug("-> +\n");
			send_pending_data(fd);
			break;
		default:
			/* XXX: Possibly drop connection instead. */
			debug("-> %02x\n", *head);
			io_buffer_consume(&cur_comm, 1);
			break;
		}
	}
}