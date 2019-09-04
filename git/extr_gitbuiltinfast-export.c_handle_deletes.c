#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct refspec_item {char* dst; scalar_t__* src; } ;
struct TYPE_2__ {int nr; struct refspec_item* items; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_oid ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 TYPE_1__ refspecs ; 

__attribute__((used)) static void handle_deletes(void)
{
	int i;
	for (i = 0; i < refspecs.nr; i++) {
		struct refspec_item *refspec = &refspecs.items[i];
		if (*refspec->src)
			continue;

		printf("reset %s\nfrom %s\n\n",
				refspec->dst, oid_to_hex(&null_oid));
	}
}