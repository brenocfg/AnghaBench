#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ec; int /*<<< orphan*/  nistp521; int /*<<< orphan*/  nistp256; int /*<<< orphan*/  nistp224; int /*<<< orphan*/  nistz256; } ;
struct TYPE_5__ {int pre_comp_type; TYPE_1__ pre_comp; } ;
typedef  TYPE_2__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_ec_pre_comp_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_nistp224_pre_comp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_nistp256_pre_comp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_nistp521_pre_comp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_nistz256_pre_comp_free (int /*<<< orphan*/ ) ; 
#define  PCT_ec 133 
#define  PCT_nistp224 132 
#define  PCT_nistp256 131 
#define  PCT_nistp521 130 
#define  PCT_nistz256 129 
#define  PCT_none 128 

void EC_pre_comp_free(EC_GROUP *group)
{
    switch (group->pre_comp_type) {
    case PCT_none:
        break;
    case PCT_nistz256:
#ifdef ECP_NISTZ256_ASM
        EC_nistz256_pre_comp_free(group->pre_comp.nistz256);
#endif
        break;
#ifndef OPENSSL_NO_EC_NISTP_64_GCC_128
    case PCT_nistp224:
        EC_nistp224_pre_comp_free(group->pre_comp.nistp224);
        break;
    case PCT_nistp256:
        EC_nistp256_pre_comp_free(group->pre_comp.nistp256);
        break;
    case PCT_nistp521:
        EC_nistp521_pre_comp_free(group->pre_comp.nistp521);
        break;
#else
    case PCT_nistp224:
    case PCT_nistp256:
    case PCT_nistp521:
        break;
#endif
    case PCT_ec:
        EC_ec_pre_comp_free(group->pre_comp.ec);
        break;
    }
    group->pre_comp.ec = NULL;
}