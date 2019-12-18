#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 scalar_t__ isarray (int /*<<< orphan*/ ) ; 
 scalar_t__ isfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr (int /*<<< orphan*/ ) ; 
 TYPE_1__* retype (TYPE_1__*,int /*<<< orphan*/ ) ; 

Tree pointer(Tree p) {
	if (isarray(p->type))
		/* assert(p->op != RIGHT || p->u.sym == NULL), */
		p = retype(p, atop(p->type));
	else if (isfunc(p->type))
		p = retype(p, ptr(p->type));
	return p;
}