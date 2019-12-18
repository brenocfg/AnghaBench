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
 int /*<<< orphan*/  BF_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * KMALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 

__attribute__((used)) static int
blf_setkey(u_int8_t **sched, const u_int8_t *key, int len)
{
	int err;

	*sched = KMALLOC(sizeof(BF_KEY),
		M_CRYPTO_DATA, M_NOWAIT|M_ZERO);
	if (*sched != NULL) {
		BF_set_key((BF_KEY *) *sched, len, key);
		err = 0;
	} else
		err = ENOMEM;
	return err;
}