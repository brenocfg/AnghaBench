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
 int AQ_MAXHIGH ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  QSZ_CONTROL_ENTRY ; 
 int USE_DEFAULT_QSZ ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getstrfromtype_locked (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setac_locked () ; 
 int sscanf (char*,char*,int*) ; 

int
getacqsize(int *qsz_val)
{
	char *str;
	int nparsed;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif
	setac_locked();
	if (getstrfromtype_locked(QSZ_CONTROL_ENTRY, &str) < 0) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-2);
	}
	if (str == NULL) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		*qsz_val = USE_DEFAULT_QSZ;
		return (0);
	}

	/* Trim off any leading white space. */
	while (*str == ' ' || *str == '\t')
		str++;

	nparsed = sscanf(str, "%d", (int *)qsz_val);

	if (nparsed != 1) {
		errno = EINVAL;
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-1);
	}

	/* The queue size must either be 0 or < AQ_MAXHIGH */
	if (*qsz_val < 0 || *qsz_val > AQ_MAXHIGH) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		qsz_val = 0L;
		errno = EINVAL;
		return (-1);
	}
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	return (0);
}