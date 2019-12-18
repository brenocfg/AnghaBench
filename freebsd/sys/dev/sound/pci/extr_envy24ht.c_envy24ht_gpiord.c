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
typedef  int u_int32_t ;
struct sc_info {TYPE_1__* cfg; } ;
struct TYPE_2__ {int subvendor; int subdevice; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24HT_CCS_GPIO_HDATA ; 
 int /*<<< orphan*/  ENVY24HT_CCS_GPIO_LDATA ; 
 int envy24ht_rdcs (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
envy24ht_gpiord(struct sc_info *sc)
{
	if (sc->cfg->subvendor == 0x153b  && sc->cfg->subdevice == 0x1150) 
	return envy24ht_rdcs(sc, ENVY24HT_CCS_GPIO_LDATA, 2);
	else
	return (envy24ht_rdcs(sc, ENVY24HT_CCS_GPIO_HDATA, 1) << 16 | envy24ht_rdcs(sc, ENVY24HT_CCS_GPIO_LDATA, 2));
}