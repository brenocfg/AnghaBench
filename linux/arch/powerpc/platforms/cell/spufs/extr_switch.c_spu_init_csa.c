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
struct spu_state {int /*<<< orphan*/  register_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  init_priv1 (struct spu_state*) ; 
 int /*<<< orphan*/  init_priv2 (struct spu_state*) ; 
 int /*<<< orphan*/  init_prob (struct spu_state*) ; 
 int /*<<< orphan*/  memset (struct spu_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int spu_alloc_lscsa (struct spu_state*) ; 

int spu_init_csa(struct spu_state *csa)
{
	int rc;

	if (!csa)
		return -EINVAL;
	memset(csa, 0, sizeof(struct spu_state));

	rc = spu_alloc_lscsa(csa);
	if (rc)
		return rc;

	spin_lock_init(&csa->register_lock);

	init_prob(csa);
	init_priv1(csa);
	init_priv2(csa);

	return 0;
}