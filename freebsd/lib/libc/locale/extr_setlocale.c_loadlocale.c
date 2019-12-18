#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__** components; } ;
struct TYPE_3__ {char* locale; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LC_COLLATE 133 
#define  LC_CTYPE 132 
#define  LC_MESSAGES 131 
#define  LC_MONETARY 130 
#define  LC_NUMERIC 129 
#define  LC_TIME 128 
 int _LDP_ERROR ; 
 int __collate_load_tables (char const*) ; 
 int __detect_path_locale () ; 
 int __messages_load_locale (char const*) ; 
 int __monetary_load_locale (char const*) ; 
 int __numeric_load_locale (char const*) ; 
 int __time_load_locale (char const*) ; 
 int __wrap_setrunelocale (char const*) ; 
 TYPE_2__ __xlocale_global_locale ; 
 char** current_categories ; 
 int errno ; 
 char** new_categories ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
loadlocale(int category)
{
	char *new = new_categories[category];
	char *old = current_categories[category];
	int (*func) (const char *);
	int saved_errno;

	if ((new[0] == '.' &&
	    (new[1] == '\0' || (new[1] == '.' && new[2] == '\0'))) ||
	    strchr(new, '/') != NULL) {
		errno = EINVAL;
		return (NULL);
	}
	saved_errno = errno;
	errno = __detect_path_locale();
	if (errno != 0)
		return (NULL);
	errno = saved_errno;

	switch (category) {
	case LC_CTYPE:
		func = __wrap_setrunelocale;
		break;
	case LC_COLLATE:
		func = __collate_load_tables;
		break;
	case LC_TIME:
		func = __time_load_locale;
		break;
	case LC_NUMERIC:
		func = __numeric_load_locale;
		break;
	case LC_MONETARY:
		func = __monetary_load_locale;
		break;
	case LC_MESSAGES:
		func = __messages_load_locale;
		break;
	default:
		errno = EINVAL;
		return (NULL);
	}

	if (strcmp(new, old) == 0)
		return (old);

	if (func(new) != _LDP_ERROR) {
		(void)strcpy(old, new);
		(void)strcpy(__xlocale_global_locale.components[category-1]->locale, new);
		return (old);
	}

	return (NULL);
}