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
struct scb {TYPE_1__* hscb; } ;
struct ahd_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ datacnt; scalar_t__ dataptr; int /*<<< orphan*/  sgptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_LIST_NULL ; 
 int /*<<< orphan*/  aic_htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ahd_setup_noxfer_scb(struct ahd_softc *ahd, struct scb *scb)
{
	scb->hscb->sgptr = aic_htole32(SG_LIST_NULL);
	scb->hscb->dataptr = 0;
	scb->hscb->datacnt = 0;
}