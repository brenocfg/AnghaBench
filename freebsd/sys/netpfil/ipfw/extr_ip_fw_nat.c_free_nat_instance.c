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
struct cfg_nat {int /*<<< orphan*/  lib; int /*<<< orphan*/  redir_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  LibAliasUninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  del_redir_spool_cfg (struct cfg_nat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cfg_nat*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_nat_instance(struct cfg_nat *ptr)
{

	del_redir_spool_cfg(ptr, &ptr->redir_chain);
	LibAliasUninit(ptr->lib);
	free(ptr, M_IPFW);
}