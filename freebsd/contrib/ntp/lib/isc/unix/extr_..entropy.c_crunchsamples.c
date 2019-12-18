#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nsamples; int /*<<< orphan*/ * extra; int /*<<< orphan*/ * samples; scalar_t__ last_delta2; scalar_t__ last_delta; int /*<<< orphan*/  last_time; } ;
typedef  TYPE_1__ sample_queue_t ;
typedef  int /*<<< orphan*/  isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  entropypool_adddata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned int) ; 
 scalar_t__ estimate_entropy (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
crunchsamples(isc_entropy_t *ent, sample_queue_t *sq) {
	unsigned int ns;
	unsigned int added;

	if (sq->nsamples < 6)
		return (0);

	added = 0;
	sq->last_time = sq->samples[0];
	sq->last_delta = 0;
	sq->last_delta2 = 0;

	/*
	 * Prime the values by adding in the first 4 samples in.  This
	 * should completely initialize the delta calculations.
	 */
	for (ns = 0; ns < 4; ns++)
		(void)estimate_entropy(sq, sq->samples[ns]);

	for (ns = 4; ns < sq->nsamples; ns++)
		added += estimate_entropy(sq, sq->samples[ns]);

	entropypool_adddata(ent, sq->samples, sq->nsamples * 4, added);
	entropypool_adddata(ent, sq->extra, sq->nsamples * 4, 0);

	/*
	 * Move the last 4 samples into the first 4 positions, and start
	 * adding new samples from that point.
	 */
	for (ns = 0; ns < 4; ns++) {
		sq->samples[ns] = sq->samples[sq->nsamples - 4 + ns];
		sq->extra[ns] = sq->extra[sq->nsamples - 4 + ns];
	}

	sq->nsamples = 4;

	return (added);
}