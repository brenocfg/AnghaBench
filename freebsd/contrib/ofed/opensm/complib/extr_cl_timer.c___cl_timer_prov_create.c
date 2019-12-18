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
typedef  int /*<<< orphan*/  cl_timer_prov_t ;
typedef  int /*<<< orphan*/  cl_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_ERROR ; 
 int /*<<< orphan*/  CL_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  CL_SUCCESS ; 
 int /*<<< orphan*/  __cl_timer_prov_cb ; 
 int /*<<< orphan*/  __cl_timer_prov_destroy () ; 
 int /*<<< orphan*/  cl_qlist_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* gp_timer_prov ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

cl_status_t __cl_timer_prov_create(void)
{
	CL_ASSERT(gp_timer_prov == NULL);

	gp_timer_prov = malloc(sizeof(cl_timer_prov_t));
	if (!gp_timer_prov)
		return (CL_INSUFFICIENT_MEMORY);
	else
		memset(gp_timer_prov, 0, sizeof(cl_timer_prov_t));

	cl_qlist_init(&gp_timer_prov->queue);

	pthread_mutex_init(&gp_timer_prov->mutex, NULL);
	pthread_cond_init(&gp_timer_prov->cond, NULL);

	if (pthread_create(&gp_timer_prov->thread, NULL,
			   __cl_timer_prov_cb, NULL)) {
		__cl_timer_prov_destroy();
		return (CL_ERROR);
	}

	return (CL_SUCCESS);
}