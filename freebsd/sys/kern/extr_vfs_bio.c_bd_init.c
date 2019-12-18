#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bufdomain {int /*<<< orphan*/  bd_run_lock; int /*<<< orphan*/ * bd_subq; int /*<<< orphan*/  bd_dirtyq; int /*<<< orphan*/ * bd_cleanq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  QUEUE_CLEAN ; 
 int /*<<< orphan*/  QUEUE_DIRTY ; 
 int /*<<< orphan*/  bq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int mp_maxid ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bd_init(struct bufdomain *bd)
{
	int i;

	bd->bd_cleanq = &bd->bd_subq[mp_maxid + 1];
	bq_init(bd->bd_cleanq, QUEUE_CLEAN, mp_maxid + 1, "bufq clean lock");
	bq_init(&bd->bd_dirtyq, QUEUE_DIRTY, -1, "bufq dirty lock");
	for (i = 0; i <= mp_maxid; i++)
		bq_init(&bd->bd_subq[i], QUEUE_CLEAN, i,
		    "bufq clean subqueue lock");
	mtx_init(&bd->bd_run_lock, "bufspace daemon run lock", NULL, MTX_DEF);
}