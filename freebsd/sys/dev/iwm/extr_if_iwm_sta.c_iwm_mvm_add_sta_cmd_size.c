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
struct iwm_softc {TYPE_1__* cfg; } ;
struct iwm_mvm_add_sta_cmd_v7 {int dummy; } ;
struct iwm_mvm_add_sta_cmd {int dummy; } ;
struct TYPE_2__ {scalar_t__ mqrx_supported; } ;

/* Variables and functions */

__attribute__((used)) static inline int
iwm_mvm_add_sta_cmd_size(struct iwm_softc *sc)
{
	return sc->cfg->mqrx_supported ? sizeof(struct iwm_mvm_add_sta_cmd) :
	    sizeof(struct iwm_mvm_add_sta_cmd_v7);
}