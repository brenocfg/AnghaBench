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
struct TYPE_5__ {int /*<<< orphan*/ * extra; int /*<<< orphan*/ * samples; } ;
typedef  TYPE_1__ sample_queue_t ;
struct TYPE_6__ {int /*<<< orphan*/  mctx; } ;
typedef  TYPE_2__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int RND_EVENTQSIZE ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
samplequeue_release(isc_entropy_t *ent, sample_queue_t *sq) {
	REQUIRE(sq->samples != NULL);
	REQUIRE(sq->extra != NULL);

	isc_mem_put(ent->mctx, sq->samples, RND_EVENTQSIZE * 4);
	isc_mem_put(ent->mctx, sq->extra, RND_EVENTQSIZE * 4);
	sq->samples = NULL;
	sq->extra = NULL;
}