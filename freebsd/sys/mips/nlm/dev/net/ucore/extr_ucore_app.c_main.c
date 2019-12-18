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
 int /*<<< orphan*/  FWD_DIST_VEC ; 
 int /*<<< orphan*/  nlm_read_ucore_rxpktrdy () ; 
 int /*<<< orphan*/  nlm_ucore_pkt_done (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_ucore_setup_poepktdistr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
	int num_cachelines = 1518 / 64 ; /* pktsize / L3 cacheline size */


	/* Spray packets to using distribution vector */
	while (1) {
		(void)nlm_read_ucore_rxpktrdy();
		nlm_ucore_setup_poepktdistr(FWD_DIST_VEC, 0, 0, 0, 0);
		nlm_ucore_pkt_done(num_cachelines, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		    0, 0);
	}

	return (0);
}