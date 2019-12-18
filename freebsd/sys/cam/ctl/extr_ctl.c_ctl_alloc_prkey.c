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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  size_t u_int ;
struct ctl_lun {int /*<<< orphan*/ ** pr_keys; int /*<<< orphan*/  lun_lock; } ;

/* Variables and functions */
 int CTL_MAX_INIT_PER_PORT ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_alloc_prkey(struct ctl_lun *lun, uint32_t residx)
{
	uint64_t *p;
	u_int i;

	i = residx/CTL_MAX_INIT_PER_PORT;
	if (lun->pr_keys[i] != NULL)
		return;
	mtx_unlock(&lun->lun_lock);
	p = malloc(sizeof(uint64_t) * CTL_MAX_INIT_PER_PORT, M_CTL,
	    M_WAITOK | M_ZERO);
	mtx_lock(&lun->lun_lock);
	if (lun->pr_keys[i] == NULL)
		lun->pr_keys[i] = p;
	else
		free(p, M_CTL);
}