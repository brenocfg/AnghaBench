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

/* Variables and functions */
 int /*<<< orphan*/  DIST_CONTROL_ENTRY ; 
 scalar_t__ getstrfromtype_locked (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setac_locked () ; 
 scalar_t__ strcasecmp (char*,char*) ; 

int
getacdist(void)
{
	char *str;
	int ret;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif
	setac_locked();
	if (getstrfromtype_locked(DIST_CONTROL_ENTRY, &str) < 0) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-2);
	}
	if (str == NULL) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (0);
	}
	if (strcasecmp(str, "on") == 0 || strcasecmp(str, "yes") == 0)
		ret = 1;
	else
		ret = 0;
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	return (ret);
}