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
struct TYPE_3__ {struct TYPE_3__* co_array; } ;

/* Variables and functions */
 int MAXCPU ; 
 int /*<<< orphan*/  M_CALLTMP ; 
 TYPE_1__** comaster ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cocleanup(void)
{
	int i;

	for (i = 0; i < MAXCPU; i++) {
		if (comaster[i]) {
			if (comaster[i]->co_array) {
				free(comaster[i]->co_array, M_CALLTMP);
				comaster[i]->co_array = NULL;
			}
			free(comaster[i], M_CALLTMP);
			comaster[i] = NULL;
		}
	}
}