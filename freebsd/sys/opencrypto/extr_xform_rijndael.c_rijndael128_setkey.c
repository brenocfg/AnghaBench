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
typedef  int /*<<< orphan*/  rijndael_ctx ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * KMALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  rijndael_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
rijndael128_setkey(u_int8_t **sched, const u_int8_t *key, int len)
{
	int err;

	if (len != 16 && len != 24 && len != 32)
		return (EINVAL);
	*sched = KMALLOC(sizeof(rijndael_ctx), M_CRYPTO_DATA,
	    M_NOWAIT|M_ZERO);
	if (*sched != NULL) {
		rijndael_set_key((rijndael_ctx *) *sched, key,
		    len * 8);
		err = 0;
	} else
		err = ENOMEM;
	return err;
}