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
struct taskqgroup {char const* tqg_name; TYPE_1__* tqg_queue; int /*<<< orphan*/  tqg_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgc_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_GTASKQUEUE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct taskqgroup* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct taskqgroup *
taskqgroup_create(const char *name)
{
	struct taskqgroup *qgroup;

	qgroup = malloc(sizeof(*qgroup), M_GTASKQUEUE, M_WAITOK | M_ZERO);
	mtx_init(&qgroup->tqg_lock, "taskqgroup", NULL, MTX_DEF);
	qgroup->tqg_name = name;
	LIST_INIT(&qgroup->tqg_queue[0].tgc_tasks);

	return (qgroup);
}