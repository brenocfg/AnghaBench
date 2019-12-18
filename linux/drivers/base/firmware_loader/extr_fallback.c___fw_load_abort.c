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
struct fw_priv {int /*<<< orphan*/  pending_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_state_aborted (struct fw_priv*) ; 
 scalar_t__ fw_sysfs_done (struct fw_priv*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fw_load_abort(struct fw_priv *fw_priv)
{
	/*
	 * There is a small window in which user can write to 'loading'
	 * between loading done and disappearance of 'loading'
	 */
	if (fw_sysfs_done(fw_priv))
		return;

	list_del_init(&fw_priv->pending_list);
	fw_state_aborted(fw_priv);
}