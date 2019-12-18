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
struct ngsock {int error; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ngsock* const) ; 

__attribute__((used)) static void
ng_socket_item_applied(void *context, int error)
{
	struct ngsock *const priv = (struct ngsock *)context;

	mtx_lock(&priv->mtx);
	priv->error = error;
	wakeup(priv);
	mtx_unlock(&priv->mtx);

}