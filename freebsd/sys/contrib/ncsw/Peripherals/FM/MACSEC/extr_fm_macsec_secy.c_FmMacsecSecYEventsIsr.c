#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {int events; int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Event ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ t_FmMacsecSecY ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int FM_MACSEC_SECY_EV_NEXT_PN ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_FM_MACSEC_SECY_EV_NEXT_PN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FmMacsecSecYEventsIsr(t_Handle h_FmMacsecSecY, uint32_t id)
{
    t_FmMacsecSecY *p_FmMacsecSecY = (t_FmMacsecSecY *)h_FmMacsecSecY;

    UNUSED(id);
    SANITY_CHECK_RETURN(p_FmMacsecSecY, E_INVALID_HANDLE);

    if (p_FmMacsecSecY->events & FM_MACSEC_SECY_EV_NEXT_PN)
        p_FmMacsecSecY->f_Event(p_FmMacsecSecY->h_App, e_FM_MACSEC_SECY_EV_NEXT_PN);
}