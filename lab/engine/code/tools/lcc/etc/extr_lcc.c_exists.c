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
struct TYPE_3__ {char* str; struct TYPE_3__* link; } ;
typedef  TYPE_1__* List ;

/* Variables and functions */
 scalar_t__ access (char*,int) ; 
 TYPE_1__* lccinputs ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 char* strsave (char*) ; 
 int verbose ; 

__attribute__((used)) static char *exists(char *name) {
	List b;

	if ( (name[0] == '/' || name[0] == '\\' || name[2] == ':')
	&& access(name, 4) == 0)
		return name;
	if (!(name[0] == '/' || name[0] == '\\' || name[2] == ':')
	&& (b = lccinputs))		
		do {
			b = b->link;
			if (b->str[0]) {
				char buf[1024];
				sprintf(buf, "%s/%s", b->str, name);
				if (access(buf, 4) == 0)
					return strsave(buf);
			} else if (access(name, 4) == 0)
				return name;
		} while (b != lccinputs);
	if (verbose > 1)
		return name;
	return 0;
}