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
struct kmsg_dumper {int active; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 scalar_t__ kmsg_dump_get_line_nolock (struct kmsg_dumper*,int,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  kmsg_dump_rewind_nolock (struct kmsg_dumper*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  xmon_end_pagination () ; 
 int /*<<< orphan*/  xmon_start_pagination () ; 

__attribute__((used)) static void
dump_log_buf(void)
{
	struct kmsg_dumper dumper = { .active = 1 };
	unsigned char buf[128];
	size_t len;

	if (setjmp(bus_error_jmp) != 0) {
		printf("Error dumping printk buffer!\n");
		return;
	}

	catch_memory_errors = 1;
	sync();

	kmsg_dump_rewind_nolock(&dumper);
	xmon_start_pagination();
	while (kmsg_dump_get_line_nolock(&dumper, false, buf, sizeof(buf), &len)) {
		buf[len] = '\0';
		printf("%s", buf);
	}
	xmon_end_pagination();

	sync();
	/* wait a little while to see if we get a machine check */
	__delay(200);
	catch_memory_errors = 0;
}