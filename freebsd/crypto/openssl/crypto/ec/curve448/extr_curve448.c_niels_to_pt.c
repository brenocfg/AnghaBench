#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* niels_t ;
typedef  TYPE_2__* curve448_point_t ;
struct TYPE_6__ {int /*<<< orphan*/  z; int /*<<< orphan*/  x; int /*<<< orphan*/  y; int /*<<< orphan*/  t; } ;
struct TYPE_5__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  ONE ; 
 int /*<<< orphan*/  gf_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niels_to_pt(curve448_point_t e, const niels_t n)
{
    gf_add(e->y, n->b, n->a);
    gf_sub(e->x, n->b, n->a);
    gf_mul(e->t, e->y, e->x);
    gf_copy(e->z, ONE);
}