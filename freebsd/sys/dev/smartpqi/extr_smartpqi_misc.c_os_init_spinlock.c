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
struct pqisrc_softstate {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  mtx_init (struct mtx*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int os_init_spinlock(struct pqisrc_softstate *softs, struct mtx *lock, 
			char *lockname)
{
    mtx_init(lock, lockname, NULL, MTX_SPIN);
    return 0;

}