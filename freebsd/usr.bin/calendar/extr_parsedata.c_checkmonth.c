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
struct fixs {char* name; int len; } ;

/* Variables and functions */
 char** fmonths ; 
 struct fixs* fnmonths ; 
 char** months ; 
 struct fixs* nmonths ; 
 size_t strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
checkmonth(char *s, size_t *len, size_t *offset, const char **month)
{
	struct fixs *n;
	int i;

	for (i = 0; fnmonths[i].name != NULL; i++) {
		n = fnmonths + i;
		if (strncasecmp(s, n->name, n->len) == 0) {
			*len = n->len;
			*month = n->name;
			*offset = i + 1;
			return (1);
		}
	}
	for (i = 0; nmonths[i].name != NULL; i++) {
		n = nmonths + i;
		if (strncasecmp(s, n->name, n->len) == 0) {
			*len = n->len;
			*month = n->name;
			*offset = i + 1;
			return (1);
		}
	}
	for (i = 0; fmonths[i] != NULL; i++) {
		*len = strlen(fmonths[i]);
		if (strncasecmp(s, fmonths[i], *len) == 0) {
			*month = fmonths[i];
			*offset = i + 1;
			return (1);
		}
	}
	for (i = 0; months[i] != NULL; i++) {
		if (strncasecmp(s, months[i], 3) == 0) {
			*len = 3;
			*month = months[i];
			*offset = i + 1;
			return (1);
		}
	}
	return (0);
}