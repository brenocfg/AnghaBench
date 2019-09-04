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
struct TYPE_6__ {scalar_t__ ha; int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ xrecord_t ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ xpparam_t ;

/* Variables and functions */
 scalar_t__ xdl_recmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_recs(xpparam_t const *xpp,
	xrecord_t *r1, xrecord_t *r2)
{
	return r1->ha == r2->ha &&
		xdl_recmatch(r1->ptr, r1->size, r2->ptr, r2->size,
			    xpp->flags);
}