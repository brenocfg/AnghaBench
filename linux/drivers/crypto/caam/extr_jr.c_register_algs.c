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
struct device {int dummy; } ;

/* Variables and functions */
 int active_devs ; 
 int /*<<< orphan*/  algs_lock ; 
 int /*<<< orphan*/  caam_algapi_hash_init (struct device*) ; 
 int /*<<< orphan*/  caam_algapi_init (struct device*) ; 
 int /*<<< orphan*/  caam_pkc_init (struct device*) ; 
 int /*<<< orphan*/  caam_qi_algapi_init (struct device*) ; 
 int /*<<< orphan*/  caam_rng_init (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void register_algs(struct device *dev)
{
	mutex_lock(&algs_lock);

	if (++active_devs != 1)
		goto algs_unlock;

	caam_algapi_init(dev);
	caam_algapi_hash_init(dev);
	caam_pkc_init(dev);
	caam_rng_init(dev);
	caam_qi_algapi_init(dev);

algs_unlock:
	mutex_unlock(&algs_lock);
}