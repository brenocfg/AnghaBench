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
struct name {char* n_name; int /*<<< orphan*/  n_type; struct name* n_flink; } ;
struct grouphead {int dummy; } ;

/* Variables and functions */
 struct grouphead* findgroup (char*) ; 
 struct name* gexpand (struct name*,struct grouphead*,int,int /*<<< orphan*/ ) ; 
 struct name* put (struct name*,struct name*) ; 
 int /*<<< orphan*/ * value (char*) ; 

struct name *
usermap(struct name *names)
{
	struct name *new, *np, *cp;
	struct grouphead *gh;
	int metoo;

	new = NULL;
	np = names;
	metoo = (value("metoo") != NULL);
	while (np != NULL) {
		if (np->n_name[0] == '\\') {
			cp = np->n_flink;
			new = put(new, np);
			np = cp;
			continue;
		}
		gh = findgroup(np->n_name);
		cp = np->n_flink;
		if (gh != NULL)
			new = gexpand(new, gh, metoo, np->n_type);
		else
			new = put(new, np);
		np = cp;
	}
	return (new);
}