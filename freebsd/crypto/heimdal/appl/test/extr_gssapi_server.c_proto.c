#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_21__ {int s_addr; } ;
struct sockaddr_in {unsigned short sin_port; TYPE_2__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_23__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_22__ {int length; int* value; } ;
struct TYPE_20__ {int length; int* value; } ;
struct gss_channel_bindings_struct {TYPE_4__ application_data; TYPE_3__ acceptor_address; void* acceptor_addrtype; TYPE_1__ initiator_address; void* initiator_addrtype; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  remote ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  scalar_t__ gss_cred_id_t ;
typedef  TYPE_5__* gss_buffer_t ;
struct TYPE_24__ {scalar_t__ length; } ;
typedef  TYPE_5__ gss_buffer_desc ;
typedef  TYPE_7__* gss_OID ;
struct TYPE_25__ {scalar_t__ length; scalar_t__ elements; } ;
struct TYPE_19__ {scalar_t__ length; int /*<<< orphan*/  elements; } ;
struct TYPE_18__ {scalar_t__ length; int /*<<< orphan*/  elements; } ;
typedef  int OM_uint32 ;

/* Variables and functions */
 void* GSS_C_AF_INET ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 scalar_t__ GSS_ERROR (int) ; 
 TYPE_17__* GSS_KRB5_MECHANISM ; 
 TYPE_16__* GSS_SPNEGO_MECHANISM ; 
 int GSS_S_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * emalloc (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ fork_flag ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int gss_accept_sec_context (int*,scalar_t__*,scalar_t__,TYPE_5__*,struct gss_channel_bindings_struct*,int /*<<< orphan*/ *,TYPE_7__**,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_err (int,int,char*) ; 
 int gss_export_sec_context (int*,scalar_t__*,TYPE_5__*) ; 
 int gss_import_sec_context (int*,TYPE_5__*,scalar_t__*) ; 
 int gss_krb5_copy_ccache (int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_buffer (int*,TYPE_5__*) ; 
 int /*<<< orphan*/  gss_release_cred (int*,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_init_context (int /*<<< orphan*/ *) ; 
 int krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int process_it (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_token (int,TYPE_5__*) ; 
 int /*<<< orphan*/  write_token (int,TYPE_5__*) ; 

__attribute__((used)) static int
proto (int sock, const char *service)
{
    struct sockaddr_in remote, local;
    socklen_t addrlen;
    gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
    gss_buffer_desc real_input_token, real_output_token;
    gss_buffer_t input_token = &real_input_token,
	output_token = &real_output_token;
    OM_uint32 maj_stat, min_stat;
    gss_name_t client_name;
    struct gss_channel_bindings_struct input_chan_bindings;
    gss_cred_id_t delegated_cred_handle = NULL;
    krb5_ccache ccache;
    u_char init_buf[4];
    u_char acct_buf[4];
    gss_OID mech_oid;
    char *mech, *p;

    addrlen = sizeof(local);
    if (getsockname (sock, (struct sockaddr *)&local, &addrlen) < 0
	|| addrlen != sizeof(local))
	err (1, "getsockname)");

    addrlen = sizeof(remote);
    if (getpeername (sock, (struct sockaddr *)&remote, &addrlen) < 0
	|| addrlen != sizeof(remote))
	err (1, "getpeername");

    input_chan_bindings.initiator_addrtype = GSS_C_AF_INET;
    input_chan_bindings.initiator_address.length = 4;
    init_buf[0] = (remote.sin_addr.s_addr >> 24) & 0xFF;
    init_buf[1] = (remote.sin_addr.s_addr >> 16) & 0xFF;
    init_buf[2] = (remote.sin_addr.s_addr >>  8) & 0xFF;
    init_buf[3] = (remote.sin_addr.s_addr >>  0) & 0xFF;

    input_chan_bindings.initiator_address.value = init_buf;
    input_chan_bindings.acceptor_addrtype = GSS_C_AF_INET;

    input_chan_bindings.acceptor_address.length = 4;
    acct_buf[0] = (local.sin_addr.s_addr >> 24) & 0xFF;
    acct_buf[1] = (local.sin_addr.s_addr >> 16) & 0xFF;
    acct_buf[2] = (local.sin_addr.s_addr >>  8) & 0xFF;
    acct_buf[3] = (local.sin_addr.s_addr >>  0) & 0xFF;
    input_chan_bindings.acceptor_address.value = acct_buf;
    input_chan_bindings.application_data.value = emalloc(4);
#if 0
    * (unsigned short *)input_chan_bindings.application_data.value =
                          remote.sin_port;
    * ((unsigned short *)input_chan_bindings.application_data.value + 1) =
                          local.sin_port;
    input_chan_bindings.application_data.length = 4;
#else
    input_chan_bindings.application_data.length = 0;
    input_chan_bindings.application_data.value = NULL;
#endif

    delegated_cred_handle = GSS_C_NO_CREDENTIAL;

    do {
	read_token (sock, input_token);
	maj_stat =
	    gss_accept_sec_context (&min_stat,
				    &context_hdl,
				    GSS_C_NO_CREDENTIAL,
				    input_token,
				    &input_chan_bindings,
				    &client_name,
				    &mech_oid,
				    output_token,
				    NULL,
				    NULL,
				    &delegated_cred_handle);
	if(GSS_ERROR(maj_stat))
	    gss_err (1, min_stat, "gss_accept_sec_context");
	if (output_token->length != 0)
	    write_token (sock, output_token);
	if (GSS_ERROR(maj_stat)) {
	    if (context_hdl != GSS_C_NO_CONTEXT)
		gss_delete_sec_context (&min_stat,
					&context_hdl,
					GSS_C_NO_BUFFER);
	    break;
	}
    } while(maj_stat & GSS_S_CONTINUE_NEEDED);

    p = (char *)mech_oid->elements;
    if (mech_oid->length == GSS_KRB5_MECHANISM->length
	&& memcmp(p, GSS_KRB5_MECHANISM->elements, mech_oid->length) == 0)
	mech = "Kerberos 5";
    else if (mech_oid->length == GSS_SPNEGO_MECHANISM->length
	&& memcmp(p, GSS_SPNEGO_MECHANISM->elements, mech_oid->length) == 0)
	mech = "SPNEGO"; /* XXX Silly, wont show up */
    else
	mech = "Unknown";

    printf("Using mech: %s\n", mech);

    if (delegated_cred_handle != GSS_C_NO_CREDENTIAL) {
       krb5_context context;

       printf("Delegated cred found\n");

       maj_stat = krb5_init_context(&context);
       maj_stat = krb5_cc_resolve(context, "FILE:/tmp/krb5cc_test", &ccache);
       maj_stat = gss_krb5_copy_ccache(&min_stat,
				       delegated_cred_handle,
				       ccache);
       if (maj_stat == 0) {
	   krb5_principal p;
	   maj_stat = krb5_cc_get_principal(context, ccache, &p);
	   if (maj_stat == 0) {
	       char *name;
	       maj_stat = krb5_unparse_name(context, p, &name);
	       if (maj_stat == 0) {
		   printf("Delegated user is: `%s'\n", name);
		   free(name);
	       }
	       krb5_free_principal(context, p);
	   }
       }
       krb5_cc_close(context, ccache);
       gss_release_cred(&min_stat, &delegated_cred_handle);
    }

    if (fork_flag) {
	pid_t pid;
	int pipefd[2];

	if (pipe (pipefd) < 0)
	    err (1, "pipe");

	pid = fork ();
	if (pid < 0)
	    err (1, "fork");
	if (pid != 0) {
	    gss_buffer_desc buf;

	    maj_stat = gss_export_sec_context (&min_stat,
					       &context_hdl,
					       &buf);
	    if (GSS_ERROR(maj_stat))
		gss_err (1, min_stat, "gss_export_sec_context");
	    write_token (pipefd[1], &buf);
	    exit (0);
	} else {
	    gss_ctx_id_t context_hdl;
	    gss_buffer_desc buf;

	    close (pipefd[1]);
	    read_token (pipefd[0], &buf);
	    close (pipefd[0]);
	    maj_stat = gss_import_sec_context (&min_stat, &buf, &context_hdl);
	    if (GSS_ERROR(maj_stat))
		gss_err (1, min_stat, "gss_import_sec_context");
	    gss_release_buffer (&min_stat, &buf);
	    return process_it (sock, context_hdl, client_name);
	}
    } else {
	return process_it (sock, context_hdl, client_name);
    }
}