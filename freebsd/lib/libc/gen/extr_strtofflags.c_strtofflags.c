#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {int /*<<< orphan*/  flag; scalar_t__ invert; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* mapping ; 
 int nmappings ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 char* strsep (char**,char*) ; 

int
strtofflags(char **stringp, u_long *setp, u_long *clrp)
{
	char *string, *p;
	int i;

	if (setp)
		*setp = 0;
	if (clrp)
		*clrp = 0;
	string = *stringp;
	while ((p = strsep(&string, "\t ,")) != NULL) {
		*stringp = p;
		if (*p == '\0')
			continue;
		for (i = 0; i < nmappings; i++) {
			if (strcmp(p, mapping[i].name + 2) == 0) {
				if (mapping[i].invert) {
					if (clrp)
						*clrp |= mapping[i].flag;
				} else {
					if (setp)
						*setp |= mapping[i].flag;
				}
				break;
			} else if (strcmp(p, mapping[i].name) == 0) {
				if (mapping[i].invert) {
					if (setp)
						*setp |= mapping[i].flag;
				} else {
					if (clrp)
						*clrp |= mapping[i].flag;
				}
				break;
			}
		}
		if (i == nmappings)
			return 1;
	}
	return 0;
}