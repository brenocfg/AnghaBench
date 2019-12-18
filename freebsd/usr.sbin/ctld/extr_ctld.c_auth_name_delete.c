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
struct auth_name {struct auth_name* an_initator_name; TYPE_1__* an_auth_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  ag_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct auth_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_next ; 
 int /*<<< orphan*/  free (struct auth_name*) ; 

__attribute__((used)) static void
auth_name_delete(struct auth_name *an)
{
	TAILQ_REMOVE(&an->an_auth_group->ag_names, an, an_next);

	free(an->an_initator_name);
	free(an);
}