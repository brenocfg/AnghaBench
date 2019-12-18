#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gf ;
typedef  TYPE_1__* curve448_point_t ;
struct TYPE_4__ {int /*<<< orphan*/  t; int /*<<< orphan*/  y; int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int GF_HEADROOM ; 
 int /*<<< orphan*/  gf_add_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_sqr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_sub_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_subx_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gf_weak_reduce (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void point_double_internal(curve448_point_t p, const curve448_point_t q,
                                  int before_double)
{
    gf a, b, c, d;

    gf_sqr(c, q->x);
    gf_sqr(a, q->y);
    gf_add_nr(d, c, a);         /* 2+e */
    gf_add_nr(p->t, q->y, q->x); /* 2+e */
    gf_sqr(b, p->t);
    gf_subx_nr(b, b, d, 3);     /* 4+e */
    gf_sub_nr(p->t, a, c);      /* 3+e */
    gf_sqr(p->x, q->z);
    gf_add_nr(p->z, p->x, p->x); /* 2+e */
    gf_subx_nr(a, p->z, p->t, 4); /* 6+e */
    if (GF_HEADROOM == 5)
        gf_weak_reduce(a);      /* or 1+e */
    gf_mul(p->x, a, b);
    gf_mul(p->z, p->t, a);
    gf_mul(p->y, p->t, d);
    if (!before_double)
        gf_mul(p->t, b, d);
}