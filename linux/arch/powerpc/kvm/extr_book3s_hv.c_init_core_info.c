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
struct kvmppc_vcore {int /*<<< orphan*/  num_threads; } ;
struct core_info {int n_subcores; struct kvmppc_vcore** vc; int /*<<< orphan*/ * subcore_threads; int /*<<< orphan*/  total_threads; int /*<<< orphan*/  max_subcore_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct core_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_core_info(struct core_info *cip, struct kvmppc_vcore *vc)
{
	memset(cip, 0, sizeof(*cip));
	cip->n_subcores = 1;
	cip->max_subcore_threads = vc->num_threads;
	cip->total_threads = vc->num_threads;
	cip->subcore_threads[0] = vc->num_threads;
	cip->vc[0] = vc;
}