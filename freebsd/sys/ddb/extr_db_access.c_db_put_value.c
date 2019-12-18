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
typedef  int db_expr_t ;
typedef  scalar_t__ db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,long long) ; 
 scalar_t__ db_write_bytes (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  kdb_reenter () ; 

void
db_put_value(db_addr_t addr, int size, db_expr_t value)
{
	char		data[sizeof(int)];
	int		i;

#if _BYTE_ORDER == _BIG_ENDIAN
	for (i = size - 1; i >= 0; i--)
#else	/* _LITTLE_ENDIAN */
	for (i = 0; i < size; i++)
#endif
	{
	    data[i] = value & 0xFF;
	    value >>= 8;
	}

	if (db_write_bytes(addr, size, data) != 0) {
		db_printf("*** error writing to address %llx ***\n",
		    (long long)addr);
		kdb_reenter();
	}
}