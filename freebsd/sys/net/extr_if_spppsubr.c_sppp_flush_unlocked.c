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
struct ifqueue {int dummy; } ;
struct sppp {struct ifqueue pp_cpq; struct ifqueue pp_fastq; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 struct sppp* IFP2SP (struct ifnet*) ; 
 TYPE_1__* SP2IFP (struct sppp*) ; 
 int /*<<< orphan*/  sppp_qflush (struct ifqueue*) ; 

__attribute__((used)) static void
sppp_flush_unlocked(struct ifnet *ifp)
{
	struct sppp *sp = IFP2SP(ifp);

	sppp_qflush ((struct ifqueue *)&SP2IFP(sp)->if_snd);
	sppp_qflush (&sp->pp_fastq);
	sppp_qflush (&sp->pp_cpq);
}