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
struct seq_file {struct drbd_connection* private; } ;
struct drbd_connection {int /*<<< orphan*/  r_timing_details; int /*<<< orphan*/  r_cb_nr; int /*<<< orphan*/  w_timing_details; int /*<<< orphan*/  w_cb_nr; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  seq_print_timing_details (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int callback_history_show(struct seq_file *m, void *ignored)
{
	struct drbd_connection *connection = m->private;
	unsigned long jif = jiffies;

	/* BUMP me if you change the file format/content/presentation */
	seq_printf(m, "v: %u\n\n", 0);

	seq_puts(m, "n\tage\tcallsite\tfn\n");
	seq_print_timing_details(m, "worker", connection->w_cb_nr, connection->w_timing_details, jif);
	seq_print_timing_details(m, "receiver", connection->r_cb_nr, connection->r_timing_details, jif);
	return 0;
}