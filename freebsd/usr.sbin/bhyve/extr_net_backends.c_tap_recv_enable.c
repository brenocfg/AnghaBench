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
struct tap_priv {int /*<<< orphan*/  mevp; } ;
struct net_backend {scalar_t__ opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  mevent_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tap_recv_enable(struct net_backend *be)
{
	struct tap_priv *priv = (struct tap_priv *)be->opaque;

	mevent_enable(priv->mevp);
}