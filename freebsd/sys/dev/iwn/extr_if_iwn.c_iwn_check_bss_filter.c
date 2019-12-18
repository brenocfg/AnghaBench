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
struct iwn_softc {TYPE_1__* rxon; } ;
struct TYPE_2__ {int filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_FILTER_BSS ; 
 int htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwn_check_bss_filter(struct iwn_softc *sc)
{
	return ((sc->rxon->filter & htole32(IWN_FILTER_BSS)) != 0);
}