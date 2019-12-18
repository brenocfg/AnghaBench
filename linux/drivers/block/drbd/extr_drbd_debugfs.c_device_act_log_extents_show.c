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
struct seq_file {struct drbd_device* private; } ;
struct drbd_device {int /*<<< orphan*/  act_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FAILED ; 
 scalar_t__ get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc_seq_dump_details (struct seq_file*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lc_seq_printf_stats (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_act_log_extents_show(struct seq_file *m, void *ignored)
{
	struct drbd_device *device = m->private;

	/* BUMP me if you change the file format/content/presentation */
	seq_printf(m, "v: %u\n\n", 0);

	if (get_ldev_if_state(device, D_FAILED)) {
		lc_seq_printf_stats(m, device->act_log);
		lc_seq_dump_details(m, device->act_log, "", NULL);
		put_ldev(device);
	}
	return 0;
}