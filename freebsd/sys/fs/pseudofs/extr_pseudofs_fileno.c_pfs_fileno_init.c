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
struct pfs_info {int /*<<< orphan*/  pi_mutex; int /*<<< orphan*/  pi_unrhdr; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int NO_PID ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int,int,int /*<<< orphan*/ *) ; 

void
pfs_fileno_init(struct pfs_info *pi)
{

	mtx_init(&pi->pi_mutex, "pfs_fileno", NULL, MTX_DEF);
	pi->pi_unrhdr = new_unrhdr(3, INT_MAX / NO_PID, &pi->pi_mutex);
}