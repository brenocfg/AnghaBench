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
struct TYPE_3__ {char* isoName; char* name; } ;

/* Variables and functions */
 TYPE_1__* allCountries ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
cclist()
{
	int i;

	printf("\nCountry codes:\n");
	for (i = 0; i < nitems(allCountries); i++)
		printf("%2s %-15.15s%s",
			allCountries[i].isoName,
			allCountries[i].name,
			((i+1)%4) == 0 ? "\n" : " ");
	printf("\n");
}