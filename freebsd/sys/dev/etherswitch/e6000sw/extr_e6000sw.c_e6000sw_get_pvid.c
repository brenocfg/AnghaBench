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
typedef  int /*<<< orphan*/  e6000sw_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PORT_VID ; 
 int PORT_VID_DEF_VID_MASK ; 
 int /*<<< orphan*/  REG_PORT (int /*<<< orphan*/ *,int) ; 
 int e6000sw_readreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
e6000sw_get_pvid(e6000sw_softc_t *sc, int port, int *pvid)
{

	if (pvid == NULL)
		return (ENXIO);

	*pvid = e6000sw_readreg(sc, REG_PORT(sc, port), PORT_VID) &
	    PORT_VID_DEF_VID_MASK;

	return (0);
}