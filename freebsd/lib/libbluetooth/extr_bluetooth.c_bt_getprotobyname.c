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
struct protoent {char* p_name; char** p_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_endprotoent () ; 
 struct protoent* bt_getprotoent () ; 
 int /*<<< orphan*/  bt_setprotoent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_stayopen ; 
 scalar_t__ strcmp (char*,char const*) ; 

struct protoent *
bt_getprotobyname(char const *name)
{
	struct protoent	 *p;
	char		**cp;

	bt_setprotoent(proto_stayopen);
	while ((p = bt_getprotoent()) != NULL) {
		if (strcmp(p->p_name, name) == 0)
			break;
		for (cp = p->p_aliases; *cp != NULL; cp++)
			if (strcmp(*cp, name) == 0)
				goto found;
	}
found:
	bt_endprotoent();

	return (p);
}