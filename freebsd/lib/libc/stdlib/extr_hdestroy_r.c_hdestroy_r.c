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
struct hsearch_data {struct __hsearch* __hsearch; } ;
struct __hsearch {struct __hsearch* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct __hsearch*) ; 

void
hdestroy_r(struct hsearch_data *htab)
{
	struct __hsearch *hsearch;

	/* Free hash table object and its entries. */
	hsearch = htab->__hsearch;
	free(hsearch->entries);
	free(hsearch);
}