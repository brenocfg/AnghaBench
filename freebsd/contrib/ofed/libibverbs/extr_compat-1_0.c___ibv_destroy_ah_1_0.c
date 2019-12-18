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
struct ibv_ah_1_0 {int /*<<< orphan*/  real_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_ah_1_0*) ; 
 int ibv_destroy_ah (int /*<<< orphan*/ ) ; 

int __ibv_destroy_ah_1_0(struct ibv_ah_1_0 *ah)
{
	int ret;

	ret = ibv_destroy_ah(ah->real_ah);
	if (ret)
		return ret;

	free(ah);
	return 0;
}