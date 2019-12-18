#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sample_queue_t ;
typedef  int /*<<< orphan*/  isc_uint32_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_9__ {int /*<<< orphan*/  samplequeue; } ;
struct TYPE_10__ {TYPE_1__ sample; } ;
struct TYPE_11__ {TYPE_2__ sources; TYPE_4__* ent; } ;
typedef  TYPE_3__ isc_entropysource_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_4__ isc_entropy_t ;

/* Variables and functions */
 scalar_t__ ISC_R_QUEUEFULL ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALID_SOURCE (TYPE_3__*) ; 
 int /*<<< orphan*/  add_entropy (TYPE_4__*,unsigned int) ; 
 scalar_t__ addsample (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crunchsamples (TYPE_4__*,int /*<<< orphan*/ *) ; 

isc_result_t
isc_entropy_addsample(isc_entropysource_t *source, isc_uint32_t sample,
		      isc_uint32_t extra)
{
	isc_entropy_t *ent;
	sample_queue_t *sq;
	unsigned int entropy;
	isc_result_t result;

	REQUIRE(VALID_SOURCE(source));

	ent = source->ent;

	LOCK(&ent->lock);

	sq = &source->sources.sample.samplequeue;
	result = addsample(sq, sample, extra);
	if (result == ISC_R_QUEUEFULL) {
		entropy = crunchsamples(ent, sq);
		add_entropy(ent, entropy);
	}

	UNLOCK(&ent->lock);

	return (result);
}