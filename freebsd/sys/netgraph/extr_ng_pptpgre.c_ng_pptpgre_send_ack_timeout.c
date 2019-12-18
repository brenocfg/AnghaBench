#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_1__* hpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_pptpgre_xmit (TYPE_1__* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ng_pptpgre_send_ack_timeout(node_p node, hook_p hook, void *arg1, int arg2)
{
	const hpriv_p hpriv = arg1;

	mtx_lock(&hpriv->mtx);
	/* Send a frame with an ack but no payload */
  	ng_pptpgre_xmit(hpriv, NULL);
	mtx_assert(&hpriv->mtx, MA_NOTOWNED);
}