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

/* Variables and functions */
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strsave (char*) ; 

__attribute__((used)) static char *first(char *list) {
	char *s = strchr(list, ';');

	if (s) {
		char buf[1024];
		strncpy(buf, list, s-list);
		buf[s-list] = '\0';
		return strsave(buf);
	} else
		return list;
}