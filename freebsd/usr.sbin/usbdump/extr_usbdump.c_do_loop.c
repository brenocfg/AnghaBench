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
typedef  int /*<<< orphan*/  uint8_t ;
struct usbcap {scalar_t__ buffer; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  EINTR 128 
 scalar_t__ doexit ; 
 int errno ; 
 int /*<<< orphan*/  fix_packets (scalar_t__,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  print_packets (scalar_t__,int) ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/ * w_arg ; 
 int /*<<< orphan*/  write_packets (struct usbcap*,scalar_t__,int) ; 

__attribute__((used)) static void
do_loop(struct usbcap *p)
{
	int cc;

	while (doexit == 0) {
		cc = read(p->fd, (uint8_t *)p->buffer, p->bufsize);
		if (cc < 0) {
			switch (errno) {
			case EINTR:
				break;
			default:
				fprintf(stderr, "read: %s\n", strerror(errno));
				return;
			}
			continue;
		}
		if (cc == 0)
			continue;

		fix_packets(p->buffer, cc);

		if (w_arg != NULL)
			write_packets(p, p->buffer, cc);
		print_packets(p->buffer, cc);
	}
}