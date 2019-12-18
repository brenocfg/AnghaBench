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
struct iser_global {int dummy; } ;
struct icl_iser_pdu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  close_conns_mutex; int /*<<< orphan*/  connlist; int /*<<< orphan*/  connlist_mutex; int /*<<< orphan*/  device_list; int /*<<< orphan*/  device_list_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISER_DBG (char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  icl_iser_ncons ; 
 int /*<<< orphan*/  icl_pdu_zone ; 
 int icl_register (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ ig ; 
 int /*<<< orphan*/  iser_limits ; 
 int /*<<< orphan*/  iser_new_conn ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icl_iser_load(void)
{
	int error;

	ISER_DBG("Starting iSER datamover...");

	icl_pdu_zone = uma_zcreate("icl_iser_pdu", sizeof(struct icl_iser_pdu),
				   NULL, NULL, NULL, NULL,
				   UMA_ALIGN_PTR, 0);
	/* FIXME: Check rc */

	refcount_init(&icl_iser_ncons, 0);

	error = icl_register("iser", true, 0, iser_limits, iser_new_conn);
	KASSERT(error == 0, ("failed to register iser"));

	memset(&ig, 0, sizeof(struct iser_global));

	/* device init is called only after the first addr resolution */
	sx_init(&ig.device_list_mutex,  "global_device_lock");
	INIT_LIST_HEAD(&ig.device_list);
	mtx_init(&ig.connlist_mutex, "iser_global_conn_lock", NULL, MTX_DEF);
	INIT_LIST_HEAD(&ig.connlist);
	sx_init(&ig.close_conns_mutex,  "global_close_conns_lock");

	return (error);
}