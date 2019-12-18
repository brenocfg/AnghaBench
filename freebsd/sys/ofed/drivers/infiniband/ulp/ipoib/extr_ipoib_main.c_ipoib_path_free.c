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
struct ipoib_path {scalar_t__ ah; int /*<<< orphan*/  queue; } ;
struct ipoib_dev_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _IF_DRAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_cm_destroy_tx (scalar_t__) ; 
 scalar_t__ ipoib_cm_get (struct ipoib_path*) ; 
 int /*<<< orphan*/  ipoib_put_ah (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ipoib_path*) ; 

void
ipoib_path_free(struct ipoib_dev_priv *priv, struct ipoib_path *path)
{

	_IF_DRAIN(&path->queue);

	if (path->ah)
		ipoib_put_ah(path->ah);
	if (ipoib_cm_get(path))
		ipoib_cm_destroy_tx(ipoib_cm_get(path));

	kfree(path);
}