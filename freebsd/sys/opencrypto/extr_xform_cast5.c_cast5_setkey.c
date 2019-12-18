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
typedef  int /*<<< orphan*/  cast_key ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * KMALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cast_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
cast5_setkey(u_int8_t **sched, const u_int8_t *key, int len)
{
	int err;

	*sched = KMALLOC(sizeof(cast_key), M_CRYPTO_DATA, M_NOWAIT|M_ZERO);
	if (*sched != NULL) {
		cast_setkey((cast_key *)*sched, key, len);
		err = 0;
	} else
		err = ENOMEM;
	return err;
}