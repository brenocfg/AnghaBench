#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nsamples; int /*<<< orphan*/ * samples; int /*<<< orphan*/ * extra; } ;
typedef  TYPE_1__ sample_queue_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  mctx; } ;
typedef  TYPE_2__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int RND_EVENTQSIZE ; 
 void* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static isc_result_t
samplesource_allocate(isc_entropy_t *ent, sample_queue_t *sq) {
	sq->samples = isc_mem_get(ent->mctx, RND_EVENTQSIZE * 4);
	if (sq->samples == NULL)
		return (ISC_R_NOMEMORY);

	sq->extra = isc_mem_get(ent->mctx, RND_EVENTQSIZE * 4);
	if (sq->extra == NULL) {
		isc_mem_put(ent->mctx, sq->samples, RND_EVENTQSIZE * 4);
		sq->samples = NULL;
		return (ISC_R_NOMEMORY);
	}

	sq->nsamples = 0;

	return (ISC_R_SUCCESS);
}