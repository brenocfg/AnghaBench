#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* jump_host; int jump_port; char* jump_user; char* jump_extra; int /*<<< orphan*/ * proxy_command; } ;
typedef  TYPE_1__ Options ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int parse_ssh_uri (char*,char**,char**,int*) ; 
 scalar_t__ parse_user_host_port (char*,char**,char**,int*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 
 void* xstrdup (char const*) ; 

int
parse_jump(const char *s, Options *o, int active)
{
	char *orig, *sdup, *cp;
	char *host = NULL, *user = NULL;
	int ret = -1, port = -1, first;

	active &= o->proxy_command == NULL && o->jump_host == NULL;

	orig = sdup = xstrdup(s);
	first = active;
	do {
		if (strcasecmp(s, "none") == 0)
			break;
		if ((cp = strrchr(sdup, ',')) == NULL)
			cp = sdup; /* last */
		else
			*cp++ = '\0';

		if (first) {
			/* First argument and configuration is active */
			if (parse_ssh_uri(cp, &user, &host, &port) == -1 ||
			    parse_user_host_port(cp, &user, &host, &port) != 0)
				goto out;
		} else {
			/* Subsequent argument or inactive configuration */
			if (parse_ssh_uri(cp, NULL, NULL, NULL) == -1 ||
			    parse_user_host_port(cp, NULL, NULL, NULL) != 0)
				goto out;
		}
		first = 0; /* only check syntax for subsequent hosts */
	} while (cp != sdup);
	/* success */
	if (active) {
		if (strcasecmp(s, "none") == 0) {
			o->jump_host = xstrdup("none");
			o->jump_port = 0;
		} else {
			o->jump_user = user;
			o->jump_host = host;
			o->jump_port = port;
			o->proxy_command = xstrdup("none");
			user = host = NULL;
			if ((cp = strrchr(s, ',')) != NULL && cp != s) {
				o->jump_extra = xstrdup(s);
				o->jump_extra[cp - s] = '\0';
			}
		}
	}
	ret = 0;
 out:
	free(orig);
	free(user);
	free(host);
	return ret;
}