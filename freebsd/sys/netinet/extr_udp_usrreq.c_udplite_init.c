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

/* Variables and functions */
 int /*<<< orphan*/  IPI_HASHFIELDS_2TUPLE ; 
 int /*<<< orphan*/  UDBHASHSIZE ; 
 int /*<<< orphan*/  V_ulitecb ; 
 int /*<<< orphan*/  V_ulitecbinfo ; 
 int /*<<< orphan*/  in_pcbinfo_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udplite_inpcb_init ; 

void
udplite_init(void)
{

	in_pcbinfo_init(&V_ulitecbinfo, "udplite", &V_ulitecb, UDBHASHSIZE,
	    UDBHASHSIZE, "udplite_inpcb", udplite_inpcb_init,
	    IPI_HASHFIELDS_2TUPLE);
}