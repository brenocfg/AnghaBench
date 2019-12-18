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
 int RANDOM_MAX ; 
 int V_hd_pmax ; 
 int V_hd_qmin ; 
 int V_hd_qthresh ; 
 unsigned long random () ; 

__attribute__((used)) static __inline int
should_backoff(int qdly, int maxqdly)
{
	unsigned long p;

	if (qdly < V_hd_qthresh) {
		p = (((RANDOM_MAX / 100) * V_hd_pmax) /
		    (V_hd_qthresh - V_hd_qmin)) * (qdly - V_hd_qmin);
	} else {
		if (qdly > V_hd_qthresh)
			p = (((RANDOM_MAX / 100) * V_hd_pmax) /
			    (maxqdly - V_hd_qthresh)) * (maxqdly - qdly);
		else
			p = (RANDOM_MAX / 100) * V_hd_pmax;
	}

	return (random() < p);
}