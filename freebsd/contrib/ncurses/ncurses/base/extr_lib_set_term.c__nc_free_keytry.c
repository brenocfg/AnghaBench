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
struct TYPE_4__ {struct TYPE_4__* sibling; struct TYPE_4__* child; } ;
typedef  TYPE_1__ TRIES ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
_nc_free_keytry(TRIES * kt)
{
    if (kt != 0) {
	_nc_free_keytry(kt->child);
	_nc_free_keytry(kt->sibling);
	free(kt);
    }
}