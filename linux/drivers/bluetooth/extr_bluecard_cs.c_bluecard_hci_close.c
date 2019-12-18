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
struct hci_dev {int dummy; } ;
struct bluecard_info {int /*<<< orphan*/  timer; TYPE_2__* p_dev; } ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  bluecard_hci_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct bluecard_info* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 

__attribute__((used)) static int bluecard_hci_close(struct hci_dev *hdev)
{
	struct bluecard_info *info = hci_get_drvdata(hdev);
	unsigned int iobase = info->p_dev->resource[0]->start;

	bluecard_hci_flush(hdev);

	/* Stop LED timer */
	del_timer_sync(&(info->timer));

	/* Disable power LED */
	outb(0x00, iobase + 0x30);

	return 0;
}