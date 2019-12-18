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
struct onoe_softc {int dummy; } ;
struct ath_ratectrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct onoe_softc*,int /*<<< orphan*/ ) ; 

void
ath_rate_detach(struct ath_ratectrl *arc)
{
	struct onoe_softc *osc = (struct onoe_softc *) arc;

	free(osc, M_DEVBUF);
}