#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mask_t ;
typedef  TYPE_1__* gf ;
struct TYPE_7__ {int* limb; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf_add (TYPE_1__*,TYPE_1__* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  gf_strong_reduce (TYPE_1__*) ; 

mask_t gf_hibit(const gf x)
{
    gf y;

    gf_add(y, x, x);
    gf_strong_reduce(y);
    return 0 - (y->limb[0] & 1);
}