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
struct rdma_cm_id {struct iser_conn* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ic_error ) (TYPE_1__*) ;} ;
struct iser_conn {TYPE_1__ icl_conn; } ;

/* Variables and functions */
 scalar_t__ iser_conn_terminate (struct iser_conn*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
iser_cleanup_handler(struct rdma_cm_id *cma_id, bool destroy)
{
	struct iser_conn *iser_conn = cma_id->context;

	if (iser_conn_terminate(iser_conn))
		iser_conn->icl_conn.ic_error(&iser_conn->icl_conn);

}