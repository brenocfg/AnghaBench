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
struct ipoib_dev_priv {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipoib_poll (struct ipoib_dev_priv*) ; 

void ipoib_ib_completion(struct ib_cq *cq, void *dev_ptr)
{
	struct ipoib_dev_priv *priv = dev_ptr;

	ipoib_poll(priv);
}