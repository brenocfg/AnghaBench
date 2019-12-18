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
struct TYPE_6__ {struct TYPE_6__** kids; int /*<<< orphan*/  type; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 scalar_t__ INDIR ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ generic (int /*<<< orphan*/ ) ; 
 scalar_t__ unqual (int /*<<< orphan*/ ) ; 
 TYPE_1__* value (TYPE_1__*) ; 
 scalar_t__ voidtype ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

Tree lvalue(Tree p) {
	if (generic(p->op) != INDIR) {
		error("lvalue required\n");
		return value(p);
	} else if (unqual(p->type) == voidtype)
		warning("`%t' used as an lvalue\n", p->type);
	return p->kids[0];
}