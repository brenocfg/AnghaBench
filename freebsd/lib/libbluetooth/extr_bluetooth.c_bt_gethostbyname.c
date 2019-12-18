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
struct hostent {char* h_name; char** h_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_endhostent () ; 
 struct hostent* bt_gethostent () ; 
 int /*<<< orphan*/  bt_sethostent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_stayopen ; 
 scalar_t__ strcasecmp (char*,char const*) ; 

struct hostent *
bt_gethostbyname(char const *name)
{
	struct hostent	*p;
	char		**cp;

	bt_sethostent(host_stayopen);
	while ((p = bt_gethostent()) != NULL) {
		if (strcasecmp(p->h_name, name) == 0)
			break;
		for (cp = p->h_aliases; *cp != NULL; cp++)
			if (strcasecmp(*cp, name) == 0)
				goto found;
	}
found:
	bt_endhostent();

	return (p);
}