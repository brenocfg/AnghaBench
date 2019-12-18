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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  BF_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  KFREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
blf_zerokey(u_int8_t **sched)
{
	bzero(*sched, sizeof(BF_KEY));
	KFREE(*sched, M_CRYPTO_DATA);
	*sched = NULL;
}