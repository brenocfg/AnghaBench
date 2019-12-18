#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  scalar_t__ u32 ;
typedef  TYPE_1__* hcb_p ;
typedef  scalar_t__ ccb_p ;
struct TYPE_6__ {int dqueueget; scalar_t__* dqueue; } ;

/* Variables and functions */
 int MAX_QUEUE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MEMORY_BARRIER () ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 scalar_t__ scr_to_cpu (scalar_t__) ; 
 scalar_t__ sym_ccb_from_dsa (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sym_complete_ok (TYPE_1__*,scalar_t__) ; 
 char* sym_name (TYPE_1__*) ; 

__attribute__((used)) static int sym_wakeup_done (hcb_p np)
{
	ccb_p cp;
	int i, n;
	u32 dsa;

	SYM_LOCK_ASSERT(MA_OWNED);

	n = 0;
	i = np->dqueueget;
	while (1) {
		dsa = scr_to_cpu(np->dqueue[i]);
		if (!dsa)
			break;
		np->dqueue[i] = 0;
		if ((i = i+2) >= MAX_QUEUE*2)
			i = 0;

		cp = sym_ccb_from_dsa(np, dsa);
		if (cp) {
			MEMORY_BARRIER();
			sym_complete_ok (np, cp);
			++n;
		}
		else
			printf ("%s: bad DSA (%x) in done queue.\n",
				sym_name(np), (u_int) dsa);
	}
	np->dqueueget = i;

	return n;
}