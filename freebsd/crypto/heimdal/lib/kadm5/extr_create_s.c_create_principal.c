#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  caller; int /*<<< orphan*/  context; } ;
typedef  TYPE_3__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  TYPE_4__* kadm5_principal_ent_t ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_rec ;
struct TYPE_15__ {int /*<<< orphan*/  principal; int /*<<< orphan*/  time; } ;
struct TYPE_16__ {TYPE_1__ created_by; int /*<<< orphan*/  principal; } ;
struct TYPE_19__ {TYPE_2__ entry; } ;
typedef  TYPE_5__ hdb_entry_ex ;
struct TYPE_18__ {int /*<<< orphan*/  principal; int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int KADM5_ATTRIBUTES ; 
 scalar_t__ KADM5_BAD_MASK ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_POLICY ; 
 scalar_t__ KADM5_UNK_POLICY ; 
 scalar_t__ _kadm5_setup_entry (TYPE_3__*,TYPE_5__*,int,TYPE_4__*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_default (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_free_principal_ent (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static kadm5_ret_t
create_principal(kadm5_server_context *context,
		 kadm5_principal_ent_t princ,
		 uint32_t mask,
		 hdb_entry_ex *ent,
		 uint32_t required_mask,
		 uint32_t forbidden_mask)
{
    kadm5_ret_t ret;
    kadm5_principal_ent_rec defrec, *defent;
    uint32_t def_mask;

    if((mask & required_mask) != required_mask)
	return KADM5_BAD_MASK;
    if((mask & forbidden_mask))
	return KADM5_BAD_MASK;
    if((mask & KADM5_POLICY) && strcmp(princ->policy, "default"))
	/* XXX no real policies for now */
	return KADM5_UNK_POLICY;
    memset(ent, 0, sizeof(*ent));
    ret  = krb5_copy_principal(context->context, princ->principal,
			       &ent->entry.principal);
    if(ret)
	return ret;

    defent = &defrec;
    ret = get_default(context, princ->principal, defent);
    if(ret) {
	defent   = NULL;
	def_mask = 0;
    } else {
	def_mask = KADM5_ATTRIBUTES | KADM5_MAX_LIFE | KADM5_MAX_RLIFE;
    }

    ret = _kadm5_setup_entry(context,
			     ent, mask | def_mask,
			     princ, mask,
			     defent, def_mask);
    if(defent)
	kadm5_free_principal_ent(context, defent);
    if (ret)
	return ret;

    ent->entry.created_by.time = time(NULL);

    return krb5_copy_principal(context->context, context->caller,
			       &ent->entry.created_by.principal);
}