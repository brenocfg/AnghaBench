#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ expires; } ;
struct TYPE_9__ {int /*<<< orphan*/  func; } ;
struct TYPE_13__ {TYPE_2__ timer; TYPE_1__ work; } ;
struct TYPE_12__ {int /*<<< orphan*/  jiffies; int /*<<< orphan*/  status; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  FD_STATUS ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int OLOGSIZE ; 
 int /*<<< orphan*/  command_status ; 
 int /*<<< orphan*/  cont ; 
 int /*<<< orphan*/  current_req ; 
 scalar_t__ delayed_work_pending (TYPE_6__*) ; 
 scalar_t__ do_floppy ; 
 int /*<<< orphan*/  fd_inb (int /*<<< orphan*/ ) ; 
 TYPE_6__ fd_timeout ; 
 TYPE_6__ fd_timer ; 
 int /*<<< orphan*/  fdc_busy ; 
 TYPE_3__ floppy_work ; 
 scalar_t__ interruptjiffies ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lasthandler ; 
 int /*<<< orphan*/  lastredo ; 
 TYPE_4__* output_log ; 
 int output_log_pos ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reply_buffer ; 
 int /*<<< orphan*/  resultjiffies ; 
 int /*<<< orphan*/  resultsize ; 
 int /*<<< orphan*/  timeout_message ; 
 scalar_t__ work_pending (TYPE_3__*) ; 

__attribute__((used)) static void show_floppy(void)
{
	int i;

	pr_info("\n");
	pr_info("floppy driver state\n");
	pr_info("-------------------\n");
	pr_info("now=%lu last interrupt=%lu diff=%lu last called handler=%ps\n",
		jiffies, interruptjiffies, jiffies - interruptjiffies,
		lasthandler);

	pr_info("timeout_message=%s\n", timeout_message);
	pr_info("last output bytes:\n");
	for (i = 0; i < OLOGSIZE; i++)
		pr_info("%2x %2x %lu\n",
			output_log[(i + output_log_pos) % OLOGSIZE].data,
			output_log[(i + output_log_pos) % OLOGSIZE].status,
			output_log[(i + output_log_pos) % OLOGSIZE].jiffies);
	pr_info("last result at %lu\n", resultjiffies);
	pr_info("last redo_fd_request at %lu\n", lastredo);
	print_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1,
		       reply_buffer, resultsize, true);

	pr_info("status=%x\n", fd_inb(FD_STATUS));
	pr_info("fdc_busy=%lu\n", fdc_busy);
	if (do_floppy)
		pr_info("do_floppy=%ps\n", do_floppy);
	if (work_pending(&floppy_work))
		pr_info("floppy_work.func=%ps\n", floppy_work.func);
	if (delayed_work_pending(&fd_timer))
		pr_info("delayed work.function=%p expires=%ld\n",
		       fd_timer.work.func,
		       fd_timer.timer.expires - jiffies);
	if (delayed_work_pending(&fd_timeout))
		pr_info("timer_function=%p expires=%ld\n",
		       fd_timeout.work.func,
		       fd_timeout.timer.expires - jiffies);

	pr_info("cont=%p\n", cont);
	pr_info("current_req=%p\n", current_req);
	pr_info("command_status=%d\n", command_status);
	pr_info("\n");
}