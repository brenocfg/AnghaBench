#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* gsskrb5_ctx ;
struct TYPE_5__ {int more_flags; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int ACCEPTOR_SUBKEY ; 
 int /*<<< orphan*/  GSS_KRB5_S_KG_NO_SUBKEY ; 
 int /*<<< orphan*/  _gsskrb5i_get_acceptor_subkey (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _gsskrb5i_get_initiator_subkey (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

OM_uint32
_gsskrb5i_get_token_key(const gsskrb5_ctx ctx,
			krb5_context context,
			krb5_keyblock **key)
{
    _gsskrb5i_get_acceptor_subkey(ctx, context, key);
    if(*key == NULL) {
	/*
	 * Only use the initiator subkey or ticket session key if an
	 * acceptor subkey was not required.
	 */
	if ((ctx->more_flags & ACCEPTOR_SUBKEY) == 0)
	    _gsskrb5i_get_initiator_subkey(ctx, context, key);
    }
    if (*key == NULL) {
	krb5_set_error_message(context, 0, "No token key available");
	return GSS_KRB5_S_KG_NO_SUBKEY;
    }
    return 0;
}