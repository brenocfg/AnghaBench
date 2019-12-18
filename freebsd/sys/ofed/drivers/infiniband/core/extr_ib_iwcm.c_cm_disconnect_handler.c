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
struct iwcm_id_private {scalar_t__ state; int /*<<< orphan*/  lock; } ;
struct iw_cm_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ IW_CM_STATE_CLOSING ; 
 scalar_t__ IW_CM_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cm_disconnect_handler(struct iwcm_id_private *cm_id_priv,
				  struct iw_cm_event *iw_event)
{
	unsigned long flags;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	if (cm_id_priv->state == IW_CM_STATE_ESTABLISHED)
		cm_id_priv->state = IW_CM_STATE_CLOSING;
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
}