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
struct TYPE_3__ {int /*<<< orphan*/  family; int /*<<< orphan*/  proto; int /*<<< orphan*/  uaddr; } ;
typedef  TYPE_1__ endpoint ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_eps(endpoint eps[], int num)
{
	int		i;

	for (i = 0; i < num; i++) {
		free(eps[i].uaddr);
		free(eps[i].proto);
		free(eps[i].family);
	}
	return;
}