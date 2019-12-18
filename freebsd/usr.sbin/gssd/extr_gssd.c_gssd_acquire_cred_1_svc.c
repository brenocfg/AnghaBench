#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct svc_req {int dummy; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
struct TYPE_9__ {int length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  ccname ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_10__ {int /*<<< orphan*/  output_cred; void* major_status; scalar_t__ minor_status; int /*<<< orphan*/  time_rec; int /*<<< orphan*/  actual_mechs; } ;
typedef  TYPE_2__ acquire_cred_res ;
struct TYPE_11__ {scalar_t__ desired_name; scalar_t__ uid; int /*<<< orphan*/  cred_usage; int /*<<< orphan*/  desired_mechs; int /*<<< orphan*/  time_req; } ;
typedef  TYPE_3__ acquire_cred_args ;

/* Variables and functions */
 char* GSSD_CREDENTIAL_CACHE_FILE ; 
 int /*<<< orphan*/  GSS_C_INITIATE ; 
 int /*<<< orphan*/  GSS_C_NO_NAME ; 
 void* GSS_S_BAD_NAME ; 
 void* GSS_S_COMPLETE ; 
 void* GSS_S_CREDENTIALS_EXPIRED ; 
 void* GSS_S_FAILURE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 char* ccfile_dirlist ; 
 scalar_t__ debug_level ; 
 int find_ccache_file (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* gss_acquire_cred (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* gss_display_name (scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gssd_find_resource (scalar_t__) ; 
 scalar_t__ gssd_get_cc_from_keytab (char*) ; 
 int /*<<< orphan*/  gssd_make_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_verbose_out (char*,...) ; 
 scalar_t__ hostbased_initiator_cred ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

bool_t
gssd_acquire_cred_1_svc(acquire_cred_args *argp, acquire_cred_res *result, struct svc_req *rqstp)
{
	gss_name_t desired_name = GSS_C_NO_NAME;
	gss_cred_id_t cred;
	char ccname[PATH_MAX + 5 + 1], *cp, *cp2;
	int gotone;
#ifndef WITHOUT_KERBEROS
	gss_buffer_desc namebuf;
	uint32_t minstat;
	krb5_error_code kret;
#endif

	memset(result, 0, sizeof(*result));
	if (argp->desired_name) {
		desired_name = gssd_find_resource(argp->desired_name);
		if (!desired_name) {
			result->major_status = GSS_S_BAD_NAME;
			gssd_verbose_out("gssd_acquire_cred: no desired name"
			    " found\n");
			return (TRUE);
		}
	}

#ifndef WITHOUT_KERBEROS
	if (hostbased_initiator_cred != 0 && argp->desired_name != 0 &&
	    argp->uid == 0 && argp->cred_usage == GSS_C_INITIATE) {
		/* This is a host based initiator name in the keytab file. */
		snprintf(ccname, sizeof(ccname), "FILE:%s",
		    GSSD_CREDENTIAL_CACHE_FILE);
		setenv("KRB5CCNAME", ccname, TRUE);
		result->major_status = gss_display_name(&result->minor_status,
		    desired_name, &namebuf, NULL);
		gssd_verbose_out("gssd_acquire_cred: desired name for host "
		    "based initiator cred major=0x%x minor=%d\n",
		    (unsigned int)result->major_status,
		    (int)result->minor_status);
		if (result->major_status != GSS_S_COMPLETE)
			return (TRUE);
		if (namebuf.length > PATH_MAX + 5) {
			result->minor_status = 0;
			result->major_status = GSS_S_FAILURE;
			return (TRUE);
		}
		memcpy(ccname, namebuf.value, namebuf.length);
		ccname[namebuf.length] = '\0';
		if ((cp = strchr(ccname, '@')) != NULL)
			*cp = '/';
		kret = gssd_get_cc_from_keytab(ccname);
		gssd_verbose_out("gssd_acquire_cred: using keytab entry for "
		    "%s, kerberos ret=%d\n", ccname, (int)kret);
		gss_release_buffer(&minstat, &namebuf);
		if (kret != 0) {
			result->minor_status = kret;
			result->major_status = GSS_S_FAILURE;
			return (TRUE);
		}
	} else
#endif /* !WITHOUT_KERBEROS */
	if (ccfile_dirlist[0] != '\0' && argp->desired_name == 0) {
		/*
		 * For the "-s" case and no name provided as an
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
			gssd_verbose_out("gssd_acquire_cred: no cred cache"
			    " file found\n");
			return (TRUE);
		}
		setenv("KRB5CCNAME", ccname, TRUE);
	} else {
		/*
		 * If there wasn't a "-s" option or the name has
		 * been provided as an argument, do it the old way.
		 * When a name is provided, it will normally exist in the
		 * default keytab file and the uid will be root.
		 */
		if (argp->desired_name != 0 && argp->uid != 0) {
			if (debug_level == 0)
				syslog(LOG_ERR, "gss_acquire_cred:"
				    " principal_name for non-root");
			else
				fprintf(stderr, "gss_acquire_cred:"
				    " principal_name for non-root\n");
		}
		snprintf(ccname, sizeof(ccname), "FILE:/tmp/krb5cc_%d",
		    (int) argp->uid);
		setenv("KRB5CCNAME", ccname, TRUE);
	}

	result->major_status = gss_acquire_cred(&result->minor_status,
	    desired_name, argp->time_req, argp->desired_mechs,
	    argp->cred_usage, &cred, &result->actual_mechs, &result->time_rec);
	gssd_verbose_out("gssd_acquire_cred: done major=0x%x minor=%d\n",
	    (unsigned int)result->major_status, (int)result->minor_status);

	if (result->major_status == GSS_S_COMPLETE)
		result->output_cred = gssd_make_resource(cred);
	else
		result->output_cred = 0;

	return (TRUE);
}