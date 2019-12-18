#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  qval; void** lval; } ;
typedef  TYPE_1__ nfsquad_t ;

/* Variables and functions */
 void* arc4random () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_cverf_mtx ; 

__attribute__((used)) static nfsquad_t
nfs_get_cverf(void)
{
	static nfsquad_t cverf;
	nfsquad_t ret;
	static int cverf_initialized = 0;

	mtx_lock(&nfs_cverf_mtx);
	if (cverf_initialized == 0) {
		cverf.lval[0] = arc4random();
		cverf.lval[1] = arc4random();
		cverf_initialized = 1;
	} else
		cverf.qval++;
	ret = cverf;
	mtx_unlock(&nfs_cverf_mtx);

	return (ret);
}