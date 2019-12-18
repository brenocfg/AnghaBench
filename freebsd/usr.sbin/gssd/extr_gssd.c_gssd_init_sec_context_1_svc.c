#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct svc_req {int dummy; } ;
struct TYPE_8__ {scalar_t__ major_status; scalar_t__ ctx; scalar_t__ minor_status; int /*<<< orphan*/  time_rec; int /*<<< orphan*/  ret_flags; int /*<<< orphan*/  output_token; int /*<<< orphan*/  actual_mech_type; } ;
typedef  TYPE_1__ init_sec_context_res ;
struct TYPE_9__ {scalar_t__ cred; scalar_t__ uid; scalar_t__ ctx; scalar_t__ name; int /*<<< orphan*/  input_token; int /*<<< orphan*/  input_chan_bindings; int /*<<< orphan*/  time_req; int /*<<< orphan*/  req_flags; int /*<<< orphan*/  mech_type; } ;
typedef  TYPE_2__ init_sec_context_args ;
typedef  void* gss_name_t ;
typedef  void* gss_ctx_id_t ;
typedef  scalar_t__ gss_cred_id_t ;
struct TYPE_10__ {int length; char* value; } ;
typedef  TYPE_3__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  enctype ;
typedef  int /*<<< orphan*/  ccname ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int ETYPE_DES_CBC_CRC ; 
 char* GSSD_CREDENTIAL_CACHE_FILE ; 
 void* GSS_C_NO_CONTEXT ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 void* GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_KRB5_SET_ALLOWABLE_ENCTYPES_X ; 
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 scalar_t__ GSS_S_CONTINUE_NEEDED ; 
 void* GSS_S_CREDENTIALS_EXPIRED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 char* ccfile_dirlist ; 
 scalar_t__ debug_level ; 
 int find_ccache_file (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gss_init_sec_context (scalar_t__*,scalar_t__,void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_cred (scalar_t__*,scalar_t__*) ; 
 scalar_t__ gss_set_cred_option (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* gssd_find_resource (scalar_t__) ; 
 scalar_t__ gssd_get_user_cred (scalar_t__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ gssd_make_resource (void*) ; 
 int /*<<< orphan*/  gssd_verbose_out (char*,...) ; 
 scalar_t__ hostbased_initiator_cred ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ use_old_des ; 

bool_t
gssd_init_sec_context_1_svc(init_sec_context_args *argp, init_sec_context_res *result, struct svc_req *rqstp)
{
	gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;
	gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
	gss_name_t name = GSS_C_NO_NAME;
	char ccname[PATH_MAX + 5 + 1], *cp, *cp2;
	int gotone, gotcred;
	OM_uint32 min_stat;
#ifndef WITHOUT_KERBEROS
	gss_buffer_desc principal_desc;
	char enctype[sizeof(uint32_t)];
	int key_enctype;
	OM_uint32 maj_stat;
#endif

	memset(result, 0, sizeof(*result));
	if (hostbased_initiator_cred != 0 && argp->cred != 0 &&
	    argp->uid == 0) {
		/*
		 * These credentials are for a host based initiator name
		 * in a keytab file, which should now have credentials
		 * in /tmp/krb5cc_gssd, because gss_acquire_cred() did
		 * the equivalent of "kinit -k".
		 */
		snprintf(ccname, sizeof(ccname), "FILE:%s",
		    GSSD_CREDENTIAL_CACHE_FILE);
	} else if (ccfile_dirlist[0] != '\0' && argp->cred == 0) {
		/*
		 * For the "-s" case and no credentials provided as an
		 * argument, search the directory list for an appropriate
		 * credential cache file. If the search fails, return failure.
		 */
		gotone = 0;
		cp = ccfile_dirlist;
		do {
			cp2 = strchr(cp, ':');
			if (cp2 != NULL)
				*cp2 = '\0';
			gotone = find_ccache_file(cp, argp->uid, ccname);
			if (gotone != 0)
				break;
			if (cp2 != NULL)
				*cp2++ = ':';
			cp = cp2;
		} while (cp != NULL && *cp != '\0');
		if (gotone == 0) {
			result->major_status = GSS_S_CREDENTIALS_EXPIRED;
			gssd_verbose_out("gssd_init_sec_context: -s no"
			    " credential cache file found for uid=%d\n",
			    (int)argp->uid);
			return (TRUE);
		}
	} else {
		/*
		 * If there wasn't a "-s" option or the credentials have
		 * been provided as an argument, do it the old way.
		 * When credentials are provided, the uid should be root.
		 */
		if (argp->cred != 0 && argp->uid != 0) {
			if (debug_level == 0)
				syslog(LOG_ERR, "gss_init_sec_context:"
				    " cred for non-root");
			else
				fprintf(stderr, "gss_init_sec_context:"
				    " cred for non-root\n");
		}
		snprintf(ccname, sizeof(ccname), "FILE:/tmp/krb5cc_%d",
		    (int) argp->uid);
	}
	setenv("KRB5CCNAME", ccname, TRUE);

	if (argp->cred) {
		cred = gssd_find_resource(argp->cred);
		if (!cred) {
			result->major_status = GSS_S_CREDENTIALS_EXPIRED;
			gssd_verbose_out("gssd_init_sec_context: cred"
			    " resource not found\n");
			return (TRUE);
		}
	}
	if (argp->ctx) {
		ctx = gssd_find_resource(argp->ctx);
		if (!ctx) {
			result->major_status = GSS_S_CONTEXT_EXPIRED;
			gssd_verbose_out("gssd_init_sec_context: context"
			    " resource not found\n");
			return (TRUE);
		}
	}
	if (argp->name) {
		name = gssd_find_resource(argp->name);
		if (!name) {
			result->major_status = GSS_S_BAD_NAME;
			gssd_verbose_out("gssd_init_sec_context: name"
			    " resource not found\n");
			return (TRUE);
		}
	}
	gotcred = 0;

#ifndef WITHOUT_KERBEROS
	if (use_old_des != 0) {
		if (cred == GSS_C_NO_CREDENTIAL) {
			/* Acquire a credential for the uid. */
			maj_stat = gssd_get_user_cred(&min_stat, argp->uid,
			    &cred);
			if (maj_stat == GSS_S_COMPLETE)
				gotcred = 1;
			else
				gssd_verbose_out("gssd_init_sec_context: "
				    "get user cred failed uid=%d major=0x%x "
				    "minor=%d\n", (int)argp->uid,
				    (unsigned int)maj_stat, (int)min_stat);
		}
		if (cred != GSS_C_NO_CREDENTIAL) {
			key_enctype = ETYPE_DES_CBC_CRC;
			enctype[0] = (key_enctype >> 24) & 0xff;
			enctype[1] = (key_enctype >> 16) & 0xff;
			enctype[2] = (key_enctype >> 8) & 0xff;
			enctype[3] = key_enctype & 0xff;
			principal_desc.length = sizeof(enctype);
			principal_desc.value = enctype;
			result->major_status = gss_set_cred_option(
			    &result->minor_status, &cred,
			    GSS_KRB5_SET_ALLOWABLE_ENCTYPES_X,
			    &principal_desc);
			gssd_verbose_out("gssd_init_sec_context: set allowable "
			    "enctype major=0x%x minor=%d\n",
			    (unsigned int)result->major_status,
			    (int)result->minor_status);
			if (result->major_status != GSS_S_COMPLETE) {
				if (gotcred != 0)
					gss_release_cred(&min_stat, &cred);
				return (TRUE);
			}
		}
	}
#endif
	result->major_status = gss_init_sec_context(&result->minor_status,
	    cred, &ctx, name, argp->mech_type,
	    argp->req_flags, argp->time_req, argp->input_chan_bindings,
	    &argp->input_token, &result->actual_mech_type,
	    &result->output_token, &result->ret_flags, &result->time_rec);
	gssd_verbose_out("gssd_init_sec_context: done major=0x%x minor=%d"
	    " uid=%d\n", (unsigned int)result->major_status,
	    (int)result->minor_status, (int)argp->uid);
	if (gotcred != 0)
		gss_release_cred(&min_stat, &cred);

	if (result->major_status == GSS_S_COMPLETE
	    || result->major_status == GSS_S_CONTINUE_NEEDED) {
		if (argp->ctx)
			result->ctx = argp->ctx;
		else
			result->ctx = gssd_make_resource(ctx);
	}

	return (TRUE);
}