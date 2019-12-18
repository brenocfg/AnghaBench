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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  listen_notify_list ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_mutex ; 
 int /*<<< orphan*/  raw_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 

__attribute__((used)) static void unregister_listen_notifier(struct notifier_block *nb)
{
	mutex_lock(&notify_mutex);
	raw_notifier_chain_unregister(&listen_notify_list, nb);
	mutex_unlock(&notify_mutex);
}