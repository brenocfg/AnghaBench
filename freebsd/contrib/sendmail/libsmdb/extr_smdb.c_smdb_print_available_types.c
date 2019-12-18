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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

void
smdb_print_available_types()
{
#ifdef NDBM
	printf("dbm\n");
#endif /* NDBM */
#ifdef NEWDB
	printf("hash\n");
	printf("btree\n");
#endif /* NEWDB */
}