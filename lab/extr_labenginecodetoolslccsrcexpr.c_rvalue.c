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
typedef  int /*<<< orphan*/  Type ;
typedef  TYPE_1__* Tree ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDIR ; 
 int /*<<< orphan*/  deref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unqual (int /*<<< orphan*/ ) ; 

Tree rvalue(Tree p) {
	Type ty = deref(p->type);

	ty = unqual(ty);
	return tree(mkop(INDIR,ty), ty, p, NULL);
}