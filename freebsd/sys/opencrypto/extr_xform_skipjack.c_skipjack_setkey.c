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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * KMALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  subkey_table_gen (int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
skipjack_setkey(u_int8_t **sched, const u_int8_t *key, int len)
{
	int err;

	/* NB: allocate all the memory that's needed at once */
	*sched = KMALLOC(10 * (sizeof(u_int8_t *) + 0x100),
		M_CRYPTO_DATA, M_NOWAIT|M_ZERO);
	if (*sched != NULL) {
		u_int8_t** key_tables = (u_int8_t**) *sched;
		u_int8_t* table = (u_int8_t*) &key_tables[10];
		int k;

		for (k = 0; k < 10; k++) {
			key_tables[k] = table;
			table += 0x100;
		}
		subkey_table_gen(key, (u_int8_t **) *sched);
		err = 0;
	} else
		err = ENOMEM;
	return err;
}