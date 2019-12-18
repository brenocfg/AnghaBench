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
struct ath_ratectrl {int dummy; } ;
struct amrr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct amrr_softc*,int /*<<< orphan*/ ) ; 

void
ath_rate_detach(struct ath_ratectrl *arc)
{
	struct amrr_softc *asc = (struct amrr_softc *) arc;

	free(asc, M_DEVBUF);
}