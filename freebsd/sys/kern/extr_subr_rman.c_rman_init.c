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
struct rman {scalar_t__ rm_start; scalar_t__ rm_type; int /*<<< orphan*/ * rm_mtx; int /*<<< orphan*/  rm_list; int /*<<< orphan*/  rm_end; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_RMAN ; 
 int M_ZERO ; 
 scalar_t__ RMAN_GAUGE ; 
 scalar_t__ RMAN_UNINIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rman*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rm_link ; 
 int /*<<< orphan*/  rman_head ; 
 int /*<<< orphan*/  rman_mtx ; 

int
rman_init(struct rman *rm)
{
	static int once = 0;

	if (once == 0) {
		once = 1;
		TAILQ_INIT(&rman_head);
		mtx_init(&rman_mtx, "rman head", NULL, MTX_DEF);
	}

	if (rm->rm_start == 0 && rm->rm_end == 0)
		rm->rm_end = ~0;
	if (rm->rm_type == RMAN_UNINIT)
		panic("rman_init");
	if (rm->rm_type == RMAN_GAUGE)
		panic("implement RMAN_GAUGE");

	TAILQ_INIT(&rm->rm_list);
	rm->rm_mtx = malloc(sizeof *rm->rm_mtx, M_RMAN, M_NOWAIT | M_ZERO);
	if (rm->rm_mtx == NULL)
		return ENOMEM;
	mtx_init(rm->rm_mtx, "rman", NULL, MTX_DEF);

	mtx_lock(&rman_mtx);
	TAILQ_INSERT_TAIL(&rman_head, rm, rm_link);
	mtx_unlock(&rman_mtx);
	return 0;
}