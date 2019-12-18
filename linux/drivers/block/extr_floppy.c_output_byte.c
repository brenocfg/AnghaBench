#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int reset; } ;
struct TYPE_3__ {char data; int status; int /*<<< orphan*/  jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,char,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* FDCS ; 
 int /*<<< orphan*/  FD_DATA ; 
 size_t OLOGSIZE ; 
 int /*<<< orphan*/  fd_outb (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc ; 
 scalar_t__ initialized ; 
 scalar_t__ is_ready_state (int) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__* output_log ; 
 size_t output_log_pos ; 
 int /*<<< orphan*/  show_floppy () ; 
 int wait_til_ready () ; 

__attribute__((used)) static int output_byte(char byte)
{
	int status = wait_til_ready();

	if (status < 0)
		return -1;

	if (is_ready_state(status)) {
		fd_outb(byte, FD_DATA);
		output_log[output_log_pos].data = byte;
		output_log[output_log_pos].status = status;
		output_log[output_log_pos].jiffies = jiffies;
		output_log_pos = (output_log_pos + 1) % OLOGSIZE;
		return 0;
	}
	FDCS->reset = 1;
	if (initialized) {
		DPRINT("Unable to send byte %x to FDC. Fdc=%x Status=%x\n",
		       byte, fdc, status);
		show_floppy();
	}
	return -1;
}