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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int A_K_NKEYS ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* arrow ; 

int
IsArrowKey(Char *name)
{
    int i;
    for (i = 0; i < A_K_NKEYS; i++)
	if (Strcmp(name, arrow[i].name) == 0)
	    return 1;
    return 0;
}