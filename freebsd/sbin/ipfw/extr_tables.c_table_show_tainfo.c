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
struct ta_cldata {int taclass; int itemsize; int itemsize6; int size; int count; } ;
typedef  int /*<<< orphan*/  ipfw_xtable_info ;

/* Variables and functions */
#define  IPFW_TACLASS_ARRAY 130 
#define  IPFW_TACLASS_HASH 129 
#define  IPFW_TACLASS_RADIX 128 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
table_show_tainfo(ipfw_xtable_info *i, struct ta_cldata *d,
    const char *af, const char *taclass)
{

	switch (d->taclass) {
	case IPFW_TACLASS_HASH:
	case IPFW_TACLASS_ARRAY:
		printf(" %salgorithm %s info\n", af, taclass);
		if (d->itemsize == d->itemsize6)
			printf("  size: %u items: %u itemsize: %u\n",
			    d->size, d->count, d->itemsize);
		else
			printf("  size: %u items: %u "
			    "itemsize4: %u itemsize6: %u\n",
			    d->size, d->count,
			    d->itemsize, d->itemsize6);
		break;
	case IPFW_TACLASS_RADIX:
		printf(" %salgorithm %s info\n", af, taclass);
		if (d->itemsize == d->itemsize6)
			printf("  items: %u itemsize: %u\n",
			    d->count, d->itemsize);
		else
			printf("  items: %u "
			    "itemsize4: %u itemsize6: %u\n",
			    d->count, d->itemsize, d->itemsize6);
		break;
	default:
		printf(" algo class: %s\n", taclass);
	}
}