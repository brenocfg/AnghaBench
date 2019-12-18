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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  s; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ strnodelist ;
typedef  int /*<<< orphan*/  filenode ;

/* Variables and functions */
 TYPE_1__* emalloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
strnode_add(strnodelist **listp, char *s, filenode *fnode)
{
	strnodelist *ent;

	ent = emalloc(sizeof *ent + strlen(s));
	ent->node = fnode;
	strcpy(ent->s, s);
	ent->next = *listp;
	*listp = ent;
}