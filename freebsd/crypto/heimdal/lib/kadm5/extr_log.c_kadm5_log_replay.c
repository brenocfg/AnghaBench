#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_8__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  enum kadm_ops { ____Placeholder_kadm_ops } kadm_ops ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_FAILURE ; 
 int /*<<< orphan*/  kadm5_log_replay_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_log_replay_delete (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_log_replay_modify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_log_replay_nop (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_log_replay_rename (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  kadm_create 132 
#define  kadm_delete 131 
#define  kadm_modify 130 
#define  kadm_nop 129 
#define  kadm_rename 128 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

kadm5_ret_t
kadm5_log_replay (kadm5_server_context *context,
		  enum kadm_ops op,
		  uint32_t ver,
		  uint32_t len,
		  krb5_storage *sp)
{
    switch (op) {
    case kadm_create :
	return kadm5_log_replay_create (context, ver, len, sp);
    case kadm_delete :
	return kadm5_log_replay_delete (context, ver, len, sp);
    case kadm_rename :
	return kadm5_log_replay_rename (context, ver, len, sp);
    case kadm_modify :
	return kadm5_log_replay_modify (context, ver, len, sp);
    case kadm_nop :
	return kadm5_log_replay_nop (context, ver, len, sp);
    default :
	krb5_set_error_message(context->context, KADM5_FAILURE,
			       "Unsupported replay op %d", (int)op);
	return KADM5_FAILURE;
    }
}