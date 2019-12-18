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
struct mem_range_softc {int mr_ndesc; struct mem_range_desc* mr_desc; } ;
struct mem_range_desc {scalar_t__ mr_base; scalar_t__ mr_len; } ;

/* Variables and functions */

__attribute__((used)) static struct mem_range_desc *
mem_range_match(struct mem_range_softc *sc, struct mem_range_desc *mrd)
{
	struct mem_range_desc *cand;
	int i;

	for (i = 0, cand = sc->mr_desc; i < sc->mr_ndesc; i++, cand++)
		if ((cand->mr_base == mrd->mr_base) &&
		    (cand->mr_len == mrd->mr_len))
			return (cand);
	return (NULL);
}