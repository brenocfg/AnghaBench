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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  harddog_in_fd ; 
 int /*<<< orphan*/  harddog_mutex ; 
 int /*<<< orphan*/  harddog_out_fd ; 
 int /*<<< orphan*/  lock ; 
 char* mconsole_notify_socket () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int start_watchdog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int stream_open (struct inode*,struct file*) ; 
 int timer_alive ; 

__attribute__((used)) static int harddog_open(struct inode *inode, struct file *file)
{
	int err = -EBUSY;
	char *sock = NULL;

	mutex_lock(&harddog_mutex);
	spin_lock(&lock);
	if(timer_alive)
		goto err;
#ifdef CONFIG_WATCHDOG_NOWAYOUT
	__module_get(THIS_MODULE);
#endif

#ifdef CONFIG_MCONSOLE
	sock = mconsole_notify_socket();
#endif
	err = start_watchdog(&harddog_in_fd, &harddog_out_fd, sock);
	if(err)
		goto err;

	timer_alive = 1;
	spin_unlock(&lock);
	mutex_unlock(&harddog_mutex);
	return stream_open(inode, file);
err:
	spin_unlock(&lock);
	mutex_unlock(&harddog_mutex);
	return err;
}