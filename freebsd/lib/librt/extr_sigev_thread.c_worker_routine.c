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
struct sigev_node {int /*<<< orphan*/  (* sn_dispatch ) (struct sigev_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,struct sigev_node*) ; 
 int /*<<< orphan*/  stub1 (struct sigev_node*) ; 
 int /*<<< orphan*/  worker_cleanup ; 

__attribute__((used)) static void *
worker_routine(void *arg)
{
	struct sigev_node *sn = arg;

	pthread_cleanup_push(worker_cleanup, sn);
	sn->sn_dispatch(sn);
	pthread_cleanup_pop(1);

	return (0);
}