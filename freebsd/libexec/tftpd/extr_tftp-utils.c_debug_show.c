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
typedef  int /*<<< orphan*/  s ;
struct TYPE_2__ {char* name; int value; } ;

/* Variables and functions */
 TYPE_1__* debugs ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

const char *
debug_show(int d)
{
	static char s[100];
	size_t space = sizeof(s);
	int i = 0;

	s[0] = '\0';
	while (debugs[i].name != NULL) {
		if (d&debugs[i].value) {
			if (s[0] != '\0')
				strlcat(s, " ", space);
			strlcat(s, debugs[i].name, space);
		}
		i++;
	}
	if (s[0] != '\0')
		return (s);
	return ("none");
}