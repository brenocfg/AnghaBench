#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 size_t MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,...) ; 

__attribute__((used)) static void
compare(DBT *db1, DBT *db2)
{
	size_t len;
	u_char *p1, *p2;

	if (db1->size != db2->size)
		printf("compare failed: key->data len %zu != data len %zu\n",
		    db1->size, db2->size);

	len = MIN(db1->size, db2->size);
	for (p1 = db1->data, p2 = db2->data; len--;)
		if (*p1++ != *p2++) {
			printf("compare failed at offset %lu\n",
			    (unsigned long)(p1 - (u_char *)db1->data));
			break;
		}
}