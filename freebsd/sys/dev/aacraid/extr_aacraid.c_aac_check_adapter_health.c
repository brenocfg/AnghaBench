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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct aac_softc {int dummy; } ;

/* Variables and functions */
 int AAC_GET_FWSTATUS (struct aac_softc*) ; 
 int AAC_KERNEL_PANIC ; 
 int AAC_UP_AND_RUNNING ; 

__attribute__((used)) static u_int32_t
aac_check_adapter_health(struct aac_softc *sc, u_int8_t *bled)
{
	u_int32_t ret;

	ret = AAC_GET_FWSTATUS(sc);

	if (ret & AAC_UP_AND_RUNNING)
		ret = 0;
	else if (ret & AAC_KERNEL_PANIC && bled)
		*bled = (ret >> 16) & 0xff;

	return (ret);
}