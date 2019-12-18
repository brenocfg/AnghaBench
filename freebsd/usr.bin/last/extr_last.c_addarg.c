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
struct TYPE_4__ {int type; char* name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ARG ;

/* Variables and functions */
 TYPE_1__* arglist ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 

__attribute__((used)) static void
addarg(int type, char *arg)
{
	ARG *cur;

	if ((cur = malloc(sizeof(ARG))) == NULL)
		xo_errx(1, "malloc failure");
	cur->next = arglist;
	cur->type = type;
	cur->name = arg;
	arglist = cur;
}