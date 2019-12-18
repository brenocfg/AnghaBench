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
 int MVNETA_RX_RING_CNT ; 
 scalar_t__ __predict_false (int) ; 

__attribute__((used)) static __inline int
rx_counter_adv(int ctr, int n)
{

	ctr += n;
	while (__predict_false(ctr >= MVNETA_RX_RING_CNT))
		ctr -= MVNETA_RX_RING_CNT;

	return (ctr);
}