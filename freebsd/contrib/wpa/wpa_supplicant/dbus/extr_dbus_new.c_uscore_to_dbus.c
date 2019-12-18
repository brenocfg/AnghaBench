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
typedef  scalar_t__ dbus_bool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ os_strlen (char const*) ; 
 char* os_zalloc (scalar_t__) ; 
 char const toupper (char const) ; 

__attribute__((used)) static char * uscore_to_dbus(const char *uscore)
{
	const char *p = uscore;
	char *str, *s;
	dbus_bool_t last_was_uscore = TRUE;

	s = str = os_zalloc(os_strlen(uscore) + 1);
	if (!str)
		return NULL;
	while (p && *p) {
		if (*p == '_') {
			last_was_uscore = TRUE;
		} else {
			*s++ = last_was_uscore ? toupper(*p) : *p;
			last_was_uscore = FALSE;
		}
		p++;
	}

	return str;
}