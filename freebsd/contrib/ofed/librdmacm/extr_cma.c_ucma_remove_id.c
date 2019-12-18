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
struct cma_id_private {scalar_t__ handle; } ;

/* Variables and functions */
 scalar_t__ IDX_MAX_INDEX ; 
 int /*<<< orphan*/  idm_clear (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ucma_idm ; 

__attribute__((used)) static void ucma_remove_id(struct cma_id_private *id_priv)
{
	if (id_priv->handle <= IDX_MAX_INDEX)
		idm_clear(&ucma_idm, id_priv->handle);
}