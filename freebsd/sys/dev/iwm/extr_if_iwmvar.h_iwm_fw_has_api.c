#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  enabled_api; } ;
struct TYPE_4__ {TYPE_1__ ucode_capa; } ;
struct iwm_softc {TYPE_2__ sc_fw; } ;

/* Variables and functions */
 int isset (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline bool
iwm_fw_has_api(struct iwm_softc *sc, unsigned int api)
{
	return isset(sc->sc_fw.ucode_capa.enabled_api, api);
}