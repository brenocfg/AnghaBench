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
typedef  int /*<<< orphan*/  u_int32_t ;
struct agg_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int agg_wrcodec (struct agg_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agg_ac97_write(kobj_t obj, void *sc, int regno, u_int32_t data)
{
	struct agg_info *ess = sc;
	int ret;

	/* XXX sound locking violation: agg_lock(ess); */
	ret = agg_wrcodec(ess, regno, data);
	/* agg_unlock(ess); */
	return ret;
}