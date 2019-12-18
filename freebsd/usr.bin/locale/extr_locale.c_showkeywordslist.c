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
struct TYPE_2__ {char* name; scalar_t__ type; char* comment; int /*<<< orphan*/  catid; } ;

/* Variables and functions */
 char* FMT ; 
 size_t NKWINFO ; 
 scalar_t__ TYPE_NUM ; 
 TYPE_1__* kwinfo ; 
 char* lookup_localecat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

void
showkeywordslist(char *substring)
{
	size_t	i;

#define	FMT "%-20s %-12s %-7s %-20s\n"

	if (substring == NULL)
		printf("List of available keywords\n\n");
	else
		printf("List of available keywords starting with '%s'\n\n",
		    substring);
	printf(FMT, "Keyword", "Category", "Type", "Comment");
	printf("-------------------- ------------ ------- --------------------\n");
	for (i = 0; i < NKWINFO; i++) {
		if (substring != NULL) {
			if (strncmp(kwinfo[i].name, substring,
			    strlen(substring)) != 0)
				continue;
		}
		printf(FMT,
			kwinfo[i].name,
			lookup_localecat(kwinfo[i].catid),
			(kwinfo[i].type == TYPE_NUM) ? "number" : "string",
			kwinfo[i].comment);
	}
}