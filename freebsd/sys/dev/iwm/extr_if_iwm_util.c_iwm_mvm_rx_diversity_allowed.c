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
struct iwm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iwm_mvm_get_valid_rx_ant (struct iwm_softc*) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

boolean_t
iwm_mvm_rx_diversity_allowed(struct iwm_softc *sc)
{
	if (num_of_ant(iwm_mvm_get_valid_rx_ant(sc)) == 1)
		return FALSE;

	/*
	 * XXX Also return FALSE when SMPS (Spatial Multiplexing Powersave)
	 *     is used on any vap (in the future).
	 */

	return TRUE;
}