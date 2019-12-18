#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_preauthtype ;
typedef  TYPE_4__* krb5_init_creds_context ;
struct TYPE_21__ {int flags; int etype_list_length; int preauth_list_length; int /*<<< orphan*/  anonymous; int /*<<< orphan*/  preauth_list; int /*<<< orphan*/  etype_list; TYPE_2__* opt_private; int /*<<< orphan*/ * address_list; int /*<<< orphan*/  proxiable; int /*<<< orphan*/  forwardable; } ;
typedef  TYPE_5__ krb5_get_init_creds_opt ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  scalar_t__ krb5_deltat ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_19__ {int canonicalize; int postdated; int renewable; int /*<<< orphan*/  request_anonymous; int /*<<< orphan*/  proxiable; int /*<<< orphan*/  forwardable; } ;
struct TYPE_17__ {scalar_t__ renew_till; } ;
struct TYPE_16__ {TYPE_1__ times; } ;
struct TYPE_20__ {int req_pac; int ic_flags; TYPE_3__ flags; int /*<<< orphan*/ * pre_auth_types; int /*<<< orphan*/ * etypes; int /*<<< orphan*/ * addrs; TYPE_12__ cred; int /*<<< orphan*/ * keyproc; int /*<<< orphan*/  pk_init_ctx; } ;
struct TYPE_18__ {int req_pac; int flags; int addressless; int /*<<< orphan*/  pk_init_ctx; int /*<<< orphan*/ * key_proc; scalar_t__ password; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  ETYPE_NULL ; 
 int KRB5_GET_INIT_CREDS_OPT_ADDRESS_LIST ; 
 int KRB5_GET_INIT_CREDS_OPT_ANONYMOUS ; 
 int KRB5_GET_INIT_CREDS_OPT_ETYPE_LIST ; 
 int KRB5_GET_INIT_CREDS_OPT_FORWARDABLE ; 
 int KRB5_GET_INIT_CREDS_OPT_PREAUTH_LIST ; 
 int KRB5_GET_INIT_CREDS_OPT_PROXIABLE ; 
 int KRB5_INIT_CREDS_CANONICALIZE ; 
#define  KRB5_INIT_CREDS_TRISTATE_FALSE 130 
#define  KRB5_INIT_CREDS_TRISTATE_TRUE 129 
#define  KRB5_INIT_CREDS_TRISTATE_UNSET 128 
 scalar_t__ KRB5_NT_ENTERPRISE_PRINCIPAL ; 
 int /*<<< orphan*/  KRB5_PADATA_NONE ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/ * default_s2k_func ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ init_cred (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_default_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,TYPE_5__*) ; 
 scalar_t__ krb5_init_creds_set_password (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 scalar_t__ krb5_init_creds_set_service (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 char* krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_principal_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_addrs ; 

__attribute__((used)) static krb5_error_code
get_init_creds_common(krb5_context context,
		      krb5_principal client,
		      krb5_deltat start_time,
		      krb5_get_init_creds_opt *options,
		      krb5_init_creds_context ctx)
{
    krb5_get_init_creds_opt *default_opt = NULL;
    krb5_error_code ret;
    krb5_enctype *etypes;
    krb5_preauthtype *pre_auth_types;

    memset(ctx, 0, sizeof(*ctx));

    if (options == NULL) {
	const char *realm = krb5_principal_get_realm(context, client);

        krb5_get_init_creds_opt_alloc (context, &default_opt);
	options = default_opt;
	krb5_get_init_creds_opt_set_default_flags(context, NULL, realm, options);
    }

    if (options->opt_private) {
	if (options->opt_private->password) {
	    ret = krb5_init_creds_set_password(context, ctx,
					       options->opt_private->password);
	    if (ret)
		goto out;
	}

	ctx->keyproc = options->opt_private->key_proc;
	ctx->req_pac = options->opt_private->req_pac;
	ctx->pk_init_ctx = options->opt_private->pk_init_ctx;
	ctx->ic_flags = options->opt_private->flags;
    } else
	ctx->req_pac = KRB5_INIT_CREDS_TRISTATE_UNSET;

    if (ctx->keyproc == NULL)
	ctx->keyproc = default_s2k_func;

    /* Enterprise name implicitly turns on canonicalize */
    if ((ctx->ic_flags & KRB5_INIT_CREDS_CANONICALIZE) ||
	krb5_principal_get_type(context, client) == KRB5_NT_ENTERPRISE_PRINCIPAL)
	ctx->flags.canonicalize = 1;

    ctx->pre_auth_types = NULL;
    ctx->addrs = NULL;
    ctx->etypes = NULL;
    ctx->pre_auth_types = NULL;

    ret = init_cred(context, &ctx->cred, client, start_time, options);
    if (ret) {
	if (default_opt)
	    krb5_get_init_creds_opt_free(context, default_opt);
	return ret;
    }

    ret = krb5_init_creds_set_service(context, ctx, NULL);
    if (ret)
	goto out;

    if (options->flags & KRB5_GET_INIT_CREDS_OPT_FORWARDABLE)
	ctx->flags.forwardable = options->forwardable;

    if (options->flags & KRB5_GET_INIT_CREDS_OPT_PROXIABLE)
	ctx->flags.proxiable = options->proxiable;

    if (start_time)
	ctx->flags.postdated = 1;
    if (ctx->cred.times.renew_till)
	ctx->flags.renewable = 1;
    if (options->flags & KRB5_GET_INIT_CREDS_OPT_ADDRESS_LIST) {
	ctx->addrs = options->address_list;
    } else if (options->opt_private) {
	switch (options->opt_private->addressless) {
	case KRB5_INIT_CREDS_TRISTATE_UNSET:
#if KRB5_ADDRESSLESS_DEFAULT == TRUE
	    ctx->addrs = &no_addrs;
#else
	    ctx->addrs = NULL;
#endif
	    break;
	case KRB5_INIT_CREDS_TRISTATE_FALSE:
	    ctx->addrs = NULL;
	    break;
	case KRB5_INIT_CREDS_TRISTATE_TRUE:
	    ctx->addrs = &no_addrs;
	    break;
	}
    }
    if (options->flags & KRB5_GET_INIT_CREDS_OPT_ETYPE_LIST) {
	if (ctx->etypes)
	    free(ctx->etypes);

	etypes = malloc((options->etype_list_length + 1)
			* sizeof(krb5_enctype));
	if (etypes == NULL) {
	    ret = ENOMEM;
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}
	memcpy (etypes, options->etype_list,
		options->etype_list_length * sizeof(krb5_enctype));
	etypes[options->etype_list_length] = ETYPE_NULL;
	ctx->etypes = etypes;
    }
    if (options->flags & KRB5_GET_INIT_CREDS_OPT_PREAUTH_LIST) {
	pre_auth_types = malloc((options->preauth_list_length + 1)
				* sizeof(krb5_preauthtype));
	if (pre_auth_types == NULL) {
	    ret = ENOMEM;
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}
	memcpy (pre_auth_types, options->preauth_list,
		options->preauth_list_length * sizeof(krb5_preauthtype));
	pre_auth_types[options->preauth_list_length] = KRB5_PADATA_NONE;
	ctx->pre_auth_types = pre_auth_types;
    }
    if (options->flags & KRB5_GET_INIT_CREDS_OPT_ANONYMOUS)
	ctx->flags.request_anonymous = options->anonymous;
    if (default_opt)
        krb5_get_init_creds_opt_free(context, default_opt);
    return 0;
 out:
    if (default_opt)
	krb5_get_init_creds_opt_free(context, default_opt);
    return ret;
}