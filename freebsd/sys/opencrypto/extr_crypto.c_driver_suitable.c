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
struct cryptoini {size_t cri_alg; struct cryptoini* cri_next; } ;
struct cryptocap {scalar_t__* cc_alg; } ;

/* Variables and functions */

__attribute__((used)) static int
driver_suitable(const struct cryptocap *cap, const struct cryptoini *cri)
{
	const struct cryptoini *cr;

	/* See if all the algorithms are supported. */
	for (cr = cri; cr; cr = cr->cri_next)
		if (cap->cc_alg[cr->cri_alg] == 0)
			return 0;
	return 1;
}