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
typedef  TYPE_1__* pniels_t ;
typedef  int /*<<< orphan*/  gf ;
typedef  TYPE_2__* curve448_point_t ;
struct TYPE_7__ {int /*<<< orphan*/  z; } ;
struct TYPE_6__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_niels_to_pt (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gf_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_pniels_to_pt(curve448_point_t p, const pniels_t pn,
                             int before_double)
{
    gf L0;

    gf_mul(L0, p->z, pn->z);
    gf_copy(p->z, L0);
    add_niels_to_pt(p, pn->n, before_double);
}