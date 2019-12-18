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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FILESZ_CONTROL_ENTRY ; 
 size_t MIN_AUDIT_FILE_SIZE ; 
 int /*<<< orphan*/  au_spacetobytes (size_t*,size_t,char) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getstrfromtype_locked (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setac_locked () ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,char*) ; 

int
getacfilesz(size_t *filesz_val)
{
	char *str;
	size_t val;
	char mult;
	int nparsed;

#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_lock(&mutex);
#endif
	setac_locked();
	if (getstrfromtype_locked(FILESZ_CONTROL_ENTRY, &str) < 0) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-2);
	}
	if (str == NULL) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		errno = EINVAL;
		return (-1);
	}

	/* Trim off any leading white space. */
	while (*str == ' ' || *str == '\t')
		str++;

	nparsed = sscanf(str, "%ju%c", (uintmax_t *)&val, &mult);

	switch (nparsed) {
	case 1:
		/* If no multiplier then assume 'B' (bytes). */
		mult = 'B';
		/* fall through */
	case 2:
		if (au_spacetobytes(filesz_val, val, mult) == 0)
			break;
		/* fall through */
	default:
		errno = EINVAL;
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		return (-1);
	}

	/*
	 * The file size must either be 0 or >= MIN_AUDIT_FILE_SIZE.  0
	 * indicates no rotation size.
	 */
	if (*filesz_val < 0 || (*filesz_val > 0 &&
		*filesz_val < MIN_AUDIT_FILE_SIZE)) {
#ifdef HAVE_PTHREAD_MUTEX_LOCK
		pthread_mutex_unlock(&mutex);
#endif
		filesz_val = 0L;
		errno = EINVAL;
		return (-1);
	}
#ifdef HAVE_PTHREAD_MUTEX_LOCK
	pthread_mutex_unlock(&mutex);
#endif
	return (0);
}