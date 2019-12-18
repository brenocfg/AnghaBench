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
struct pfs_info {int /*<<< orphan*/  pi_mutex; int /*<<< orphan*/ * pi_unrhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
pfs_fileno_uninit(struct pfs_info *pi)
{

	delete_unrhdr(pi->pi_unrhdr);
	pi->pi_unrhdr = NULL;
	mtx_destroy(&pi->pi_mutex);
}