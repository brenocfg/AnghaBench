#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ipaasize; int buf4size; int buf6size; int /*<<< orphan*/  mctx; scalar_t__ magic; struct TYPE_5__* buf6; struct TYPE_5__* buf4; struct TYPE_5__* ipaa; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_IFITER (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ use_GAA ; 
 int use_GAA_determined ; 

void
isc_interfaceiter_destroy(isc_interfaceiter_t **iterp) {
	isc_interfaceiter_t *iter;

	REQUIRE(iterp != NULL);
	iter = *iterp;
	REQUIRE(VALID_IFITER(iter));
	REQUIRE(use_GAA_determined);

	if (use_GAA) {
		REQUIRE(NULL == iter->buf4);
		REQUIRE(NULL == iter->buf4);
		if (iter->ipaa != NULL)
			isc_mem_put(iter->mctx, iter->ipaa, iter->ipaasize);
	} else {
		REQUIRE(NULL == iter->ipaa);
		if (iter->buf4 != NULL)
			isc_mem_put(iter->mctx, iter->buf4, iter->buf4size);
		if (iter->buf6 != NULL)
			isc_mem_put(iter->mctx, iter->buf6, iter->buf6size);
	}

	iter->magic = 0;
	isc_mem_put(iter->mctx, iter, sizeof(*iter));
	*iterp = NULL;
}