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
struct nai_realm {char* realm; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcasecmp (char*,char const*) ; 
 char* os_strchr (char*,char) ; 
 char* os_strdup (char*) ; 

__attribute__((used)) static int nai_realm_match(struct nai_realm *realm, const char *home_realm)
{
	char *tmp, *pos, *end;
	int match = 0;

	if (realm->realm == NULL || home_realm == NULL)
		return 0;

	if (os_strchr(realm->realm, ';') == NULL)
		return os_strcasecmp(realm->realm, home_realm) == 0;

	tmp = os_strdup(realm->realm);
	if (tmp == NULL)
		return 0;

	pos = tmp;
	while (*pos) {
		end = os_strchr(pos, ';');
		if (end)
			*end = '\0';
		if (os_strcasecmp(pos, home_realm) == 0) {
			match = 1;
			break;
		}
		if (end == NULL)
			break;
		pos = end + 1;
	}

	os_free(tmp);

	return match;
}