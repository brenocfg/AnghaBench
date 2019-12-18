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
struct rt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_DEBUG_INTR ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
rt_pse_fq_empty(struct rt_softc *sc)
{

	RT_DPRINTF(sc, RT_DEBUG_INTR,
	    "PSE free Q empty threshold reached & forced drop "
		    "condition occurred.\n");
}