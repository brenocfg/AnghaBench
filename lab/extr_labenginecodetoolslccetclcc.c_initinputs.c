#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* str; struct TYPE_4__* link; } ;
typedef  TYPE_1__* List ;

/* Variables and functions */
 int /*<<< orphan*/  append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * com ; 
 int /*<<< orphan*/  concat (char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  ilist ; 
 char* inputs ; 
 TYPE_1__* lccinputs ; 
 int /*<<< orphan*/ * llist ; 
 TYPE_1__* path2list (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void initinputs(void) {
	char *s = getenv("LCCINPUTS");
	List b;

	if (s == 0 || (s = inputs)[0] == 0)
		s = ".";
	if (s) {
		lccinputs = path2list(s);
		if ((b = lccinputs))
			do {
				b = b->link;
				if (strcmp(b->str, ".") != 0) {
					ilist = append(concat("-I", b->str), ilist);
					if (strstr(com[1], "win32") == NULL)
						llist[0] = append(concat("-L", b->str), llist[0]);
				} else
					b->str = "";
			} while (b != lccinputs);
	}
}