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
typedef  int /*<<< orphan*/  zil_commit_waiter_t ;
typedef  int /*<<< orphan*/  lwb_t ;

/* Variables and functions */
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* zil_lwb_cache ; 
 int /*<<< orphan*/ * zil_lwb_cons ; 
 int /*<<< orphan*/ * zil_lwb_dest ; 
 void* zil_zcw_cache ; 

void
zil_init(void)
{
	zil_lwb_cache = kmem_cache_create("zil_lwb_cache",
	    sizeof (lwb_t), 0, zil_lwb_cons, zil_lwb_dest, NULL, NULL, NULL, 0);

	zil_zcw_cache = kmem_cache_create("zil_zcw_cache",
	    sizeof (zil_commit_waiter_t), 0, NULL, NULL, NULL, NULL, NULL, 0);
}