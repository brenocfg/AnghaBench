#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 TYPE_1__* domains ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
rdlist()
{
	int i;

	printf("\nRegulatory domains:\n\n");
	for (i = 0; i < nitems(domains); i++)
		printf("%-15s%s", domains[i].name,
			((i+1)%5) == 0 ? "\n" : "");
	printf("\n");
}