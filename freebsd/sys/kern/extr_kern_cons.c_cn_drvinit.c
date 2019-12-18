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

/* Variables and functions */
 int MTX_NOWITNESS ; 
 int MTX_SPIN ; 
 int /*<<< orphan*/  cnputs_mtx ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int use_cnputs_mtx ; 

__attribute__((used)) static void
cn_drvinit(void *unused)
{

	mtx_init(&cnputs_mtx, "cnputs_mtx", NULL, MTX_SPIN | MTX_NOWITNESS);
	use_cnputs_mtx = 1;
}