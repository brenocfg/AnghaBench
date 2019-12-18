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
struct fw_priv {int dummy; } ;
struct firmware {struct fw_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_state_aborted (struct fw_priv*) ; 
 int /*<<< orphan*/  fw_state_is_aborted (struct fw_priv*) ; 

__attribute__((used)) static void fw_abort_batch_reqs(struct firmware *fw)
{
	struct fw_priv *fw_priv;

	/* Loaded directly? */
	if (!fw || !fw->priv)
		return;

	fw_priv = fw->priv;
	if (!fw_state_is_aborted(fw_priv))
		fw_state_aborted(fw_priv);
}