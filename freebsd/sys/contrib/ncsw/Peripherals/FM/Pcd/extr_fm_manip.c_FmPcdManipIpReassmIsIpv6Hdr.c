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
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {scalar_t__ hdr; } ;
struct TYPE_5__ {TYPE_1__ reassmParams; } ;
typedef  TYPE_2__ t_FmPcdManip ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 scalar_t__ HEADER_TYPE_IPv6 ; 

bool FmPcdManipIpReassmIsIpv6Hdr(t_Handle h_Manip)
{
    t_FmPcdManip *p_Manip = (t_FmPcdManip *)h_Manip;

    ASSERT_COND(p_Manip);

    return (p_Manip->reassmParams.hdr == HEADER_TYPE_IPv6);
}