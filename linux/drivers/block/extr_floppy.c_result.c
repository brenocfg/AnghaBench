#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_DATA ; 
 int MAX_REPLIES ; 
 int STATUS_BUSY ; 
 int STATUS_DIR ; 
 int STATUS_DMA ; 
 int STATUS_READY ; 
 int /*<<< orphan*/  fd_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc ; 
 scalar_t__ initialized ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/ * reply_buffer ; 
 int /*<<< orphan*/  resultjiffies ; 
 int resultsize ; 
 int /*<<< orphan*/  show_floppy () ; 
 int wait_til_ready () ; 

__attribute__((used)) static int result(void)
{
	int i;
	int status = 0;

	for (i = 0; i < MAX_REPLIES; i++) {
		status = wait_til_ready();
		if (status < 0)
			break;
		status &= STATUS_DIR | STATUS_READY | STATUS_BUSY | STATUS_DMA;
		if ((status & ~STATUS_BUSY) == STATUS_READY) {
			resultjiffies = jiffies;
			resultsize = i;
			return i;
		}
		if (status == (STATUS_DIR | STATUS_READY | STATUS_BUSY))
			reply_buffer[i] = fd_inb(FD_DATA);
		else
			break;
	}
	if (initialized) {
		DPRINT("get result error. Fdc=%d Last status=%x Read bytes=%d\n",
		       fdc, status, i);
		show_floppy();
	}
	FDCS->reset = 1;
	return -1;
}