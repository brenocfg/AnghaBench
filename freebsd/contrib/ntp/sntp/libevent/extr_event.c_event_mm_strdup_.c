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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t EV_SIZE_MAX ; 
 char* _strdup (char const*) ; 
 int /*<<< orphan*/  errno ; 
 char* memcpy (void*,char const*,size_t) ; 
 void* mm_malloc_fn_ (size_t) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 

char *
event_mm_strdup_(const char *str)
{
	if (!str) {
		errno = EINVAL;
		return NULL;
	}

	if (mm_malloc_fn_) {
		size_t ln = strlen(str);
		void *p = NULL;
		if (ln == EV_SIZE_MAX)
			goto error;
		p = mm_malloc_fn_(ln+1);
		if (p)
			return memcpy(p, str, ln+1);
	} else
#ifdef _WIN32
		return _strdup(str);
#else
		return strdup(str);
#endif

error:
	errno = ENOMEM;
	return NULL;
}