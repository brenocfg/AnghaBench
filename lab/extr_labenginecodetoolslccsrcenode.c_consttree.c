#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  Tree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnsttree (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ isarray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isint (int /*<<< orphan*/ ) ; 

Tree consttree(unsigned n, Type ty) {
	if (isarray(ty))
		ty = atop(ty);
	else assert(isint(ty));
	return cnsttree(ty, (unsigned long)n);
}