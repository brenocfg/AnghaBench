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
struct passwd {int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 char* estrdup (int /*<<< orphan*/ ) ; 
 char* get_default_username () ; 
 char* get_pobox (char const**) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
parse_pobox (char *a0, const char **host, const char **user)
{
    const char *h, *u;
    char *p;
    int po = 0;

    if (a0 == NULL) {

	*user = getenv ("USERNAME");
	if (*user == NULL) {
	    struct passwd *pwd = getpwuid (getuid ());

	    if (pwd == NULL)
		errx (1, "Who are you?");
	    *user = estrdup (pwd->pw_name);
	}
	*host = get_pobox (user);
	return;
    }

    /* if the specification starts with po:, remember this information */
    if(strncmp(a0, "po:", 3) == 0) {
	a0 += 3;
	po++;
    }
    /* if there is an `@', the hostname is after it, otherwise at the
       beginning of the string */
    p = strchr(a0, '@');
    if(p != NULL) {
	*p++ = '\0';
	h = p;
    } else {
	h = a0;
    }
    /* if there is a `:', the username comes before it, otherwise at
       the beginning of the string */
    p = strchr(a0, ':');
    if(p != NULL) {
	*p++ = '\0';
	u = p;
    } else {
	u = a0;
    }
    if(h == u) {
	/* some inconsistent compatibility with various mailers */
	if(po) {
	    h = get_pobox (&u);
	} else {
	    u = get_default_username ();
	    if (u == NULL)
		errx (1, "Who are you?");
	}
    }
    *host = h;
    *user = u;
}