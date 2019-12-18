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
struct ecore_mcast_ramrod_params {int mcast_list_len; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_mcast_cmd { ____Placeholder_ecore_mcast_cmd } ecore_mcast_cmd ;

/* Variables and functions */
 int ECORE_MCAST_CMD_DEL ; 
 int ECORE_MCAST_CMD_RESTORE ; 
 int ECORE_SUCCESS ; 

__attribute__((used)) static int ecore_mcast_validate_e1h(struct bxe_softc *sc,
				    struct ecore_mcast_ramrod_params *p,
				    enum ecore_mcast_cmd cmd)
{
	/* Mark, that there is a work to do */
	if ((cmd == ECORE_MCAST_CMD_DEL) || (cmd == ECORE_MCAST_CMD_RESTORE))
		p->mcast_list_len = 1;

	return ECORE_SUCCESS;
}