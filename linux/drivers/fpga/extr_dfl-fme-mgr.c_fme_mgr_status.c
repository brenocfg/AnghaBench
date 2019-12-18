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
typedef  int /*<<< orphan*/  u64 ;
struct fpga_manager {struct fme_mgr_priv* priv; } ;
struct fme_mgr_priv {int /*<<< orphan*/  pr_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_error_to_mgr_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 fme_mgr_status(struct fpga_manager *mgr)
{
	struct fme_mgr_priv *priv = mgr->priv;

	return pr_error_to_mgr_status(priv->pr_error);
}