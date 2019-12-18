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
 scalar_t__ getstrfromtype_locked (char const*,char**) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setac_locked () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
getaccommon(const char *name, char *auditstr, int len)
{
	char *str;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif
	setac_locked();
	if (getstrfromtype_locked(name, &str) < 0) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-2);
	}

	/*
	 * getstrfromtype_locked() can return NULL for an empty value -- make
	 * sure to handle this by coercing the NULL back into an empty string.
	 */
	if (str != NULL && (strlen(str) >= (size_t)len)) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-3);
	}
	strlcpy(auditstr, str != NULL ? str : "", len);
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	return (0);
}