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
struct ck_rhs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_RHS_PROBE_RH ; 
 int ck_rhs_put_internal (struct ck_rhs*,unsigned long,void const*,int /*<<< orphan*/ ) ; 

bool
ck_rhs_put_unique(struct ck_rhs *hs,
    unsigned long h,
    const void *key)
{

	return ck_rhs_put_internal(hs, h, key, CK_RHS_PROBE_RH);
}