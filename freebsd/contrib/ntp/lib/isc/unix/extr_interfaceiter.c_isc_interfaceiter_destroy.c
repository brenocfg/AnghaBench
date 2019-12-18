#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bufsize; int /*<<< orphan*/  mctx; scalar_t__ magic; struct TYPE_6__* buf; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_IFITER (TYPE_1__*) ; 
 int /*<<< orphan*/  internal_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
isc_interfaceiter_destroy(isc_interfaceiter_t **iterp)
{
	isc_interfaceiter_t *iter;
	REQUIRE(iterp != NULL);
	iter = *iterp;
	REQUIRE(VALID_IFITER(iter));

	internal_destroy(iter);
	if (iter->buf != NULL)
		isc_mem_put(iter->mctx, iter->buf, iter->bufsize);

	iter->magic = 0;
	isc_mem_put(iter->mctx, iter, sizeof(*iter));
	*iterp = NULL;
}