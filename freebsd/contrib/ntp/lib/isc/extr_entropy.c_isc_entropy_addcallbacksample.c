#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sample_queue_t ;
typedef  int /*<<< orphan*/  isc_uint32_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  samplequeue; } ;
struct TYPE_7__ {TYPE_1__ callback; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ sources; } ;
typedef  TYPE_3__ isc_entropysource_t ;

/* Variables and functions */
 scalar_t__ ENTROPY_SOURCETYPE_CALLBACK ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_SOURCE (TYPE_3__*) ; 
 int /*<<< orphan*/  addsample (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

isc_result_t
isc_entropy_addcallbacksample(isc_entropysource_t *source, isc_uint32_t sample,
			      isc_uint32_t extra)
{
	sample_queue_t *sq;
	isc_result_t result;

	REQUIRE(VALID_SOURCE(source));
	REQUIRE(source->type == ENTROPY_SOURCETYPE_CALLBACK);

	sq = &source->sources.callback.samplequeue;
	result = addsample(sq, sample, extra);

	return (result);
}