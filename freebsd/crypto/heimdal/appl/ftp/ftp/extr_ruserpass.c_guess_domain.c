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
struct addrinfo {char* ai_canonname; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ gethostname (char*,size_t) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static char *
guess_domain (char *hostname_str, size_t sz)
{
    struct addrinfo *ai, *a;
    struct addrinfo hints;
    int error;
    char *dot;

    if (gethostname (hostname_str, sz) < 0) {
	strlcpy (hostname_str, "", sz);
	return "";
    }
    dot = strchr (hostname_str, '.');
    if (dot != NULL)
	return dot + 1;

    memset (&hints, 0, sizeof(hints));
    hints.ai_flags = AI_CANONNAME;

    error = getaddrinfo (hostname_str, NULL, &hints, &ai);
    if (error)
	return hostname_str;

    for (a = ai; a != NULL; a = a->ai_next)
	if (a->ai_canonname != NULL) {
	    strlcpy (hostname_str, ai->ai_canonname, sz);
	    break;
	}
    freeaddrinfo (ai);
    dot = strchr (hostname_str, '.');
    if (dot != NULL)
	return dot + 1;
    else
	return hostname_str;
}