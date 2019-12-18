#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  execute; } ;
struct TYPE_6__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  flags; int /*<<< orphan*/  execute; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static PLAN *
palloc(OPTION *option)
{
	PLAN *new;

	if ((new = malloc(sizeof(PLAN))) == NULL)
		err(1, NULL);
	new->execute = option->execute;
	new->flags = option->flags;
	new->next = NULL;
	return new;
}