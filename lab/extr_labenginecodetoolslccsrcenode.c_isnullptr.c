#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
typedef  TYPE_4__* Tree ;
struct TYPE_9__ {scalar_t__ i; scalar_t__ u; int /*<<< orphan*/ * p; } ;
struct TYPE_8__ {TYPE_2__ v; } ;
struct TYPE_11__ {TYPE_1__ u; int /*<<< orphan*/  op; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ CNST ; 
 scalar_t__ INT ; 
 scalar_t__ UNSIGNED ; 
 scalar_t__ generic (int /*<<< orphan*/ ) ; 
 scalar_t__ isvoidptr (TYPE_3__*) ; 
 TYPE_3__* unqual (int /*<<< orphan*/ ) ; 

int isnullptr(Tree e) {
	Type ty = unqual(e->type);

	return generic(e->op) == CNST
	    && ((ty->op == INT      && e->u.v.i == 0)
	     || (ty->op == UNSIGNED && e->u.v.u == 0)
	     || (isvoidptr(ty)      && e->u.v.p == NULL));
}