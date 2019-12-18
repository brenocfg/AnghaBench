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
struct TYPE_2__ {char* name; int id; } ;

/* Variables and functions */
 TYPE_1__* ani_labels ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void
list_labels(void)
{
	int i;

	for (i = 0; ani_labels[i].name != NULL; i++) {
		printf("%s (%d)\n", ani_labels[i].name, ani_labels[i].id);
	}
}