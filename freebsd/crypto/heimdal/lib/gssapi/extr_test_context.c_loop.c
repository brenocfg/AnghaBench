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
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  scalar_t__ gss_cred_id_t ;
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int GSS_C_CONF_FLAG ; 
 int GSS_C_DCE_STYLE ; 
 int GSS_C_DELEG_FLAG ; 
 int GSS_C_DELEG_POLICY_FLAG ; 
 int GSS_C_INTEG_FLAG ; 
 int GSS_C_MUTUAL_FLAG ; 
 int /*<<< orphan*/  GSS_C_NO_CHANNEL_BINDINGS ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 scalar_t__ GSS_ERROR (int) ; 
 int GSS_S_CONTINUE_NEEDED ; 
 int client_time_offset ; 
 scalar_t__ dce_style_flag ; 
 scalar_t__ deleg_flag ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int gss_accept_sec_context (int*,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int gss_import_name (int*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gss_init_sec_context (int*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_oid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_buffer (int*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_name (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gssapi_err (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsskrb5_get_time_offset (int*) ; 
 int /*<<< orphan*/  gsskrb5_set_time_offset (int) ; 
 int max_loops ; 
 scalar_t__ mutual_auth_flag ; 
 scalar_t__ policy_deleg_flag ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/ * rk_UNCONST (char const*) ; 
 scalar_t__ server_no_deleg_flag ; 
 int server_time_offset ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ verbose_flag ; 

__attribute__((used)) static void
loop(gss_OID mechoid,
     gss_OID nameoid, const char *target,
     gss_cred_id_t init_cred,
     gss_ctx_id_t *sctx, gss_ctx_id_t *cctx,
     gss_OID *actual_mech,
     gss_cred_id_t *deleg_cred)
{
    int server_done = 0, client_done = 0;
    int num_loops = 0;
    OM_uint32 maj_stat, min_stat;
    gss_name_t gss_target_name;
    gss_buffer_desc input_token, output_token;
    OM_uint32 flags = 0, ret_cflags, ret_sflags;
    gss_OID actual_mech_client;
    gss_OID actual_mech_server;

    *actual_mech = GSS_C_NO_OID;

    flags |= GSS_C_INTEG_FLAG;
    flags |= GSS_C_CONF_FLAG;

    if (mutual_auth_flag)
	flags |= GSS_C_MUTUAL_FLAG;
    if (dce_style_flag)
	flags |= GSS_C_DCE_STYLE;
    if (deleg_flag)
	flags |= GSS_C_DELEG_FLAG;
    if (policy_deleg_flag)
	flags |= GSS_C_DELEG_POLICY_FLAG;

    input_token.value = rk_UNCONST(target);
    input_token.length = strlen(target);

    maj_stat = gss_import_name(&min_stat,
			       &input_token,
			       nameoid,
			       &gss_target_name);
    if (GSS_ERROR(maj_stat))
	err(1, "import name creds failed with: %d", maj_stat);

    input_token.length = 0;
    input_token.value = NULL;

    while (!server_done || !client_done) {
	num_loops++;

	gsskrb5_set_time_offset(client_time_offset);

	maj_stat = gss_init_sec_context(&min_stat,
					init_cred,
					cctx,
					gss_target_name,
					mechoid,
					flags,
					0,
					NULL,
					&input_token,
					&actual_mech_client,
					&output_token,
					&ret_cflags,
					NULL);
	if (GSS_ERROR(maj_stat))
	    errx(1, "init_sec_context: %s",
		 gssapi_err(maj_stat, min_stat, mechoid));
	if (maj_stat & GSS_S_CONTINUE_NEEDED)
	    ;
	else
	    client_done = 1;

	gsskrb5_get_time_offset(&client_time_offset);

	if (client_done && server_done)
	    break;

	if (input_token.length != 0)
	    gss_release_buffer(&min_stat, &input_token);

	gsskrb5_set_time_offset(server_time_offset);

	maj_stat = gss_accept_sec_context(&min_stat,
					  sctx,
					  GSS_C_NO_CREDENTIAL,
					  &output_token,
					  GSS_C_NO_CHANNEL_BINDINGS,
					  NULL,
					  &actual_mech_server,
					  &input_token,
					  &ret_sflags,
					  NULL,
					  deleg_cred);
	if (GSS_ERROR(maj_stat))
		errx(1, "accept_sec_context: %s",
		     gssapi_err(maj_stat, min_stat, actual_mech_server));

	gsskrb5_get_time_offset(&server_time_offset);

	if (output_token.length != 0)
	    gss_release_buffer(&min_stat, &output_token);

	if (maj_stat & GSS_S_CONTINUE_NEEDED)
	    ;
	else
	    server_done = 1;
    }
    if (output_token.length != 0)
	gss_release_buffer(&min_stat, &output_token);
    if (input_token.length != 0)
	gss_release_buffer(&min_stat, &input_token);
    gss_release_name(&min_stat, &gss_target_name);

    if (deleg_flag || policy_deleg_flag) {
	if (server_no_deleg_flag) {
	    if (*deleg_cred != GSS_C_NO_CREDENTIAL)
		errx(1, "got delegated cred but didn't expect one");
	} else if (*deleg_cred == GSS_C_NO_CREDENTIAL)
	    errx(1, "asked for delegarated cred but did get one");
    } else if (*deleg_cred != GSS_C_NO_CREDENTIAL)
	  errx(1, "got deleg_cred cred but didn't ask");

    if (gss_oid_equal(actual_mech_server, actual_mech_client) == 0)
	errx(1, "mech mismatch");
    *actual_mech = actual_mech_server;

    if (max_loops && num_loops > max_loops)
	errx(1, "num loops %d was lager then max loops %d",
	     num_loops, max_loops);

    if (verbose_flag) {
	printf("server time offset: %d\n", server_time_offset);
	printf("client time offset: %d\n", client_time_offset);
	printf("num loops %d\n", num_loops);
    }
}