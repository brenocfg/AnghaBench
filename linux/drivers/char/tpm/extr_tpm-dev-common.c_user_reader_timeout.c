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
struct timer_list {int dummy; } ;
struct file_priv {int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 struct file_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct file_priv* priv ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_tgid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_read_timer ; 

__attribute__((used)) static void user_reader_timeout(struct timer_list *t)
{
	struct file_priv *priv = from_timer(priv, t, user_read_timer);

	pr_warn("TPM user space timeout is deprecated (pid=%d)\n",
		task_tgid_nr(current));

	schedule_work(&priv->timeout_work);
}