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
struct TYPE_2__ {char* sstr; } ;

/* Variables and functions */
 scalar_t__ STORAGE_STRSPACE ; 
 char* endest ; 
 char* ep ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_1__* mstack ; 
 int sp ; 
 scalar_t__* sstack ; 
 int strsize ; 
 char* strspace ; 

void
enlarge_strspace(void)
{
	char *newstrspace;
	int i;

	strsize *= 2;
	newstrspace = malloc(strsize + 1);
	if (!newstrspace)
		errx(1, "string space overflow");
	memcpy(newstrspace, strspace, strsize/2);
	for (i = 0; i <= sp; i++)
		if (sstack[i] == STORAGE_STRSPACE)
			mstack[i].sstr = (mstack[i].sstr - strspace)
			    + newstrspace;
	ep = (ep-strspace) + newstrspace;
	free(strspace);
	strspace = newstrspace;
	endest = strspace + strsize;
}