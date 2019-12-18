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
struct vas_window {int /*<<< orphan*/  pid; scalar_t__ tx_win; int /*<<< orphan*/  cop; int /*<<< orphan*/  hvwc_map; } ;
struct seq_file {struct vas_window* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cop_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vas_mutex ; 

__attribute__((used)) static int info_show(struct seq_file *s, void *private)
{
	struct vas_window *window = s->private;

	mutex_lock(&vas_mutex);

	/* ensure window is not unmapped */
	if (!window->hvwc_map)
		goto unlock;

	seq_printf(s, "Type: %s, %s\n", cop_to_str(window->cop),
					window->tx_win ? "Send" : "Receive");
	seq_printf(s, "Pid : %d\n", window->pid);

unlock:
	mutex_unlock(&vas_mutex);
	return 0;
}