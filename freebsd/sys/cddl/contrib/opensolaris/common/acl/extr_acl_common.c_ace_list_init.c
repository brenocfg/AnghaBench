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
struct TYPE_3__ {int dfacl_flag; scalar_t__ seen; int /*<<< orphan*/  state; scalar_t__ hasmask; scalar_t__ acl_mask; scalar_t__ numgroups; scalar_t__ numusers; int /*<<< orphan*/  other_obj; int /*<<< orphan*/  group_obj; int /*<<< orphan*/  user_obj; } ;
typedef  TYPE_1__ ace_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ace_unused ; 
 int /*<<< orphan*/  acevals_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ace_list_init(ace_list_t *al, int dfacl_flag)
{
	acevals_init(&al->user_obj, 0);
	acevals_init(&al->group_obj, 0);
	acevals_init(&al->other_obj, 0);
	al->numusers = 0;
	al->numgroups = 0;
	al->acl_mask = 0;
	al->hasmask = 0;
	al->state = ace_unused;
	al->seen = 0;
	al->dfacl_flag = dfacl_flag;
}