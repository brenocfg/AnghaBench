#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pfsync_bucket {TYPE_2__* b_sc; } ;
struct TYPE_4__ {TYPE_1__* sc_ifp; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_LOCK (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_UNLOCK (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  pfsync_push (struct pfsync_bucket*) ; 

__attribute__((used)) static void
pfsync_timeout(void *arg)
{
	struct pfsync_bucket *b = arg;

	CURVNET_SET(b->b_sc->sc_ifp->if_vnet);
	PFSYNC_BUCKET_LOCK(b);
	pfsync_push(b);
	PFSYNC_BUCKET_UNLOCK(b);
	CURVNET_RESTORE();
}