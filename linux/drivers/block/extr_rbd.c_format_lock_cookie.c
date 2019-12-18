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
struct rbd_device {int /*<<< orphan*/  watch_mutex; int /*<<< orphan*/  watch_cookie; } ;

/* Variables and functions */
 char* RBD_LOCK_COOKIE_PREFIX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void format_lock_cookie(struct rbd_device *rbd_dev, char *buf)
{
	mutex_lock(&rbd_dev->watch_mutex);
	sprintf(buf, "%s %llu", RBD_LOCK_COOKIE_PREFIX, rbd_dev->watch_cookie);
	mutex_unlock(&rbd_dev->watch_mutex);
}