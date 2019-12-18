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
struct svc_rpc_gss_callback {int /*<<< orphan*/  cb_callback; } ;
typedef  int /*<<< orphan*/  rpc_gss_callback_t ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPC_GSS_ER_SYSTEMERROR ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct svc_rpc_gss_callback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _rpc_gss_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_link ; 
 struct svc_rpc_gss_callback* mem_alloc (int) ; 
 int /*<<< orphan*/  svc_rpc_gss_callbacks ; 
 int /*<<< orphan*/  svc_rpc_gss_lock ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

bool_t
rpc_gss_set_callback(rpc_gss_callback_t *cb)
{
	struct svc_rpc_gss_callback *scb;

	scb = mem_alloc(sizeof(struct svc_rpc_gss_callback));
	if (!scb) {
		_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, ENOMEM);
		return (FALSE);
	}
	scb->cb_callback = *cb;
	sx_xlock(&svc_rpc_gss_lock);
	SLIST_INSERT_HEAD(&svc_rpc_gss_callbacks, scb, cb_link);
	sx_xunlock(&svc_rpc_gss_lock);

	return (TRUE);
}