#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pair ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {struct TYPE_5__* cdr; int /*<<< orphan*/  car; } ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  error (char*) ; 

pair
cons(caddr_t car, pair cdr)
{
	pair foo = calloc(1, sizeof(*foo));
	if (!foo)
		error("no memory for cons.");
	foo->car = car;
	foo->cdr = cdr;
	return (foo);
}