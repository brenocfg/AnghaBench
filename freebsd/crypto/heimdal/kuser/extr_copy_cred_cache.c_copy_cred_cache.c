#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_5__ {scalar_t__ endtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  keytype; } ;
struct TYPE_6__ {int /*<<< orphan*/  server; TYPE_2__ times; int /*<<< orphan*/  flags; TYPE_1__ session; } ;
struct ctx {TYPE_3__ mcreds; int /*<<< orphan*/  whichfields; } ;
struct copy_cred_cache_options {scalar_t__ krbtgt_only_flag; scalar_t__ fcache_version_integer; scalar_t__ valid_for_string; scalar_t__ flags_string; int /*<<< orphan*/  enctype_string; int /*<<< orphan*/  service_string; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_TC_MATCH_FLAGS ; 
 int /*<<< orphan*/  KRB5_TC_MATCH_KEYTYPE ; 
 int /*<<< orphan*/  KRB5_TC_MATCH_TIMES ; 
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  kcc_context ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_copy_match_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctx*,unsigned int*) ; 
 char* krb5_cc_default_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_fcache_version (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_string_to_enctype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matchfunc ; 
 int /*<<< orphan*/  memset (struct ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_ticket_flags (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_time (scalar_t__,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
copy_cred_cache(struct copy_cred_cache_options *opt, int argc, char **argv)
{
    krb5_error_code ret;
    const char *from_name, *to_name;
    krb5_ccache from_ccache, to_ccache;
    unsigned int matched;
    struct ctx ctx;

    memset(&ctx, 0, sizeof(ctx));

    if (opt->service_string) {
	ret = krb5_parse_name(kcc_context, opt->service_string, &ctx.mcreds.server);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "%s", opt->service_string);
    }
    if (opt->enctype_string) {
	krb5_enctype enctype;
	ret = krb5_string_to_enctype(kcc_context, opt->enctype_string, &enctype);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "%s", opt->enctype_string);
	ctx.whichfields |= KRB5_TC_MATCH_KEYTYPE;
	ctx.mcreds.session.keytype = enctype;
    }
    if (opt->flags_string) {
	parse_ticket_flags(kcc_context, opt->flags_string, &ctx.mcreds.flags);
	ctx.whichfields |= KRB5_TC_MATCH_FLAGS;
    }
    if (opt->valid_for_string) {
	time_t t = parse_time(opt->valid_for_string, "s");
	if(t < 0)
	    errx(1, "unknown time \"%s\"", opt->valid_for_string);
	ctx.mcreds.times.endtime = time(NULL) + t;
	ctx.whichfields |= KRB5_TC_MATCH_TIMES;
    }
    if (opt->fcache_version_integer)
	krb5_set_fcache_version(kcc_context, opt->fcache_version_integer);

    if (argc == 1) {
	from_name = krb5_cc_default_name(kcc_context);
	to_name = argv[0];
    } else {
	from_name = argv[0];
	to_name = argv[1];
    }

    ret = krb5_cc_resolve(kcc_context, from_name, &from_ccache);
    if (ret)
	krb5_err(kcc_context, 1, ret, "%s", from_name);

    if (opt->krbtgt_only_flag) {
	krb5_principal client;
	ret = krb5_cc_get_principal(kcc_context, from_ccache, &client);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "getting default principal");
	ret = krb5_make_principal(kcc_context, &ctx.mcreds.server,
				  krb5_principal_get_realm(kcc_context, client),
				  KRB5_TGS_NAME,
				  krb5_principal_get_realm(kcc_context, client),
				  NULL);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "constructing krbtgt principal");
	krb5_free_principal(kcc_context, client);
    }
    ret = krb5_cc_resolve(kcc_context, to_name, &to_ccache);
    if (ret)
	krb5_err(kcc_context, 1, ret, "%s", to_name);

    ret = krb5_cc_copy_match_f(kcc_context, from_ccache, to_ccache,
			       matchfunc, &ctx, &matched);
    if (ret)
	krb5_err(kcc_context, 1, ret, "copying cred cache");

    krb5_cc_close(kcc_context, from_ccache);
    if(matched == 0)
	krb5_cc_destroy(kcc_context, to_ccache);
    else
	krb5_cc_close(kcc_context, to_ccache);

    return matched == 0;
}