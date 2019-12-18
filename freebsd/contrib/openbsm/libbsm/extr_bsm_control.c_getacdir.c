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
 int /*<<< orphan*/  DIR_CONTROL_ENTRY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * fp ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getstrfromtype_locked (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ inacdir ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ptrmoved ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 

int
getacdir(char *name, int len)
{
	char *dir;
	int ret = 0;

	/*
	 * Check if another function was called between successive calls to
	 * getacdir.
	 */
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif
	if (inacdir && ptrmoved) {
		ptrmoved = 0;
		if (fp != NULL)
			fseek(fp, 0, SEEK_SET);
		ret = 2;
	}
	if (getstrfromtype_locked(DIR_CONTROL_ENTRY, &dir) < 0) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-2);
	}
	if (dir == NULL) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-1);
	}
	if (strlen(dir) >= (size_t)len) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-3);
	}
	strlcpy(name, dir, len);
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	return (ret);
}