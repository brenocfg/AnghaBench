#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  h_Hc; } ;
typedef  TYPE_1__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_DpaaFD ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  FmHcTxConf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (scalar_t__,int /*<<< orphan*/ ) ; 

void FM_PCD_HcTxConf(t_Handle h_FmPcd, t_DpaaFD *p_Fd)
{
    t_FmPcd                 *p_FmPcd = (t_FmPcd*)h_FmPcd;

    SANITY_CHECK_RETURN(h_FmPcd, E_INVALID_STATE);

    FmHcTxConf(p_FmPcd->h_Hc, p_Fd);
}