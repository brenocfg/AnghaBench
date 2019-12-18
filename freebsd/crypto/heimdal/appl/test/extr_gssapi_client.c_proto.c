#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_17__ {int s_addr; } ;
struct sockaddr_storage {unsigned short sin_port; TYPE_2__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_19__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_18__ {int length; int* value; } ;
struct TYPE_16__ {int length; int* value; } ;
struct gss_channel_bindings_struct {TYPE_4__ application_data; TYPE_3__ acceptor_address; void* acceptor_addrtype; TYPE_1__ initiator_address; void* initiator_addrtype; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  remote ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  TYPE_5__* gss_buffer_t ;
struct TYPE_20__ {scalar_t__ length; char* value; } ;
typedef  TYPE_5__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int OM_uint32 ;

/* Variables and functions */
 void* GSS_C_AF_INET ; 
 int /*<<< orphan*/  GSS_C_INDEFINITE ; 
 int /*<<< orphan*/  GSS_C_INITIATE ; 
 int GSS_C_MUTUAL_FLAG ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_C_NO_OID_SET ; 
 int /*<<< orphan*/  GSS_C_NT_HOSTBASED_SERVICE ; 
 int GSS_C_SEQUENCE_FLAG ; 
 scalar_t__ GSS_ERROR (int) ; 
 int GSS_S_CONTINUE_NEEDED ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int do_trans (int,scalar_t__) ; 
 int /*<<< orphan*/ * emalloc (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ fork_flag ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int gss_acquire_cred_with_password (int*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_err (int,int,char*,...) ; 
 int gss_export_sec_context (int*,scalar_t__*,TYPE_5__*) ; 
 int gss_import_name (int*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gss_import_sec_context (int*,TYPE_5__*,scalar_t__*) ; 
 int gss_init_sec_context (int*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (int*,TYPE_5__*) ; 
 int /*<<< orphan*/  mech ; 
 char* password ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  read_token (int,TYPE_5__*) ; 
 int /*<<< orphan*/  select_mech (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  write_token (int,TYPE_5__*) ; 

__attribute__((used)) static int
proto (int sock, const char *hostname, const char *service)
{
    struct sockaddr_storage remote, local;
    socklen_t addrlen;

    int context_established = 0;
    gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
    gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;
    gss_buffer_desc real_input_token, real_output_token;
    gss_buffer_t input_token = &real_input_token,
	output_token = &real_output_token;
    OM_uint32 maj_stat, min_stat;
    gss_name_t server;
    gss_buffer_desc name_token;
    u_char init_buf[4];
    u_char acct_buf[4];
    gss_OID mech_oid;
    char *str;

    mech_oid = select_mech(mech);

    name_token.length = asprintf (&str,
				  "%s@%s", service, hostname);
    if (str == NULL)
	errx(1, "malloc - out of memory");
    name_token.value = str;

    maj_stat = gss_import_name (&min_stat,
				&name_token,
				GSS_C_NT_HOSTBASED_SERVICE,
				&server);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat,
		 "Error importing name `%s@%s':\n", service, hostname);

    if (password) {
        gss_buffer_desc pw;

        pw.value = password;
        pw.length = strlen(password);

        maj_stat = gss_acquire_cred_with_password(&min_stat,
						  GSS_C_NO_NAME,
						  &pw,
						  GSS_C_INDEFINITE,
						  GSS_C_NO_OID_SET,
						  GSS_C_INITIATE,
						  &cred,
						  NULL,
						  NULL);
        if (GSS_ERROR(maj_stat))
            gss_err (1, min_stat,
                     "Error acquiring default initiator credentials");
    }

    addrlen = sizeof(local);
    if (getsockname (sock, (struct sockaddr *)&local, &addrlen) < 0
	|| addrlen > sizeof(local))
	err (1, "getsockname(%s)", hostname);

    addrlen = sizeof(remote);
    if (getpeername (sock, (struct sockaddr *)&remote, &addrlen) < 0
	|| addrlen > sizeof(remote))
	err (1, "getpeername(%s)", hostname);

    input_token->length = 0;
    output_token->length = 0;

#if 0
    struct gss_channel_bindings_struct input_chan_bindings;

    input_chan_bindings.initiator_addrtype = GSS_C_AF_INET;
    input_chan_bindings.initiator_address.length = 4;
    init_buf[0] = (local.sin_addr.s_addr >> 24) & 0xFF;
    init_buf[1] = (local.sin_addr.s_addr >> 16) & 0xFF;
    init_buf[2] = (local.sin_addr.s_addr >>  8) & 0xFF;
    init_buf[3] = (local.sin_addr.s_addr >>  0) & 0xFF;
    input_chan_bindings.initiator_address.value = init_buf;

    input_chan_bindings.acceptor_addrtype = GSS_C_AF_INET;
    input_chan_bindings.acceptor_address.length = 4;
    acct_buf[0] = (remote.sin_addr.s_addr >> 24) & 0xFF;
    acct_buf[1] = (remote.sin_addr.s_addr >> 16) & 0xFF;
    acct_buf[2] = (remote.sin_addr.s_addr >>  8) & 0xFF;
    acct_buf[3] = (remote.sin_addr.s_addr >>  0) & 0xFF;
    input_chan_bindings.acceptor_address.value = acct_buf;

    input_chan_bindings.application_data.value = emalloc(4);
    * (unsigned short*)input_chan_bindings.application_data.value = local.sin_port;
    * ((unsigned short *)input_chan_bindings.application_data.value + 1) = remote.sin_port;
    input_chan_bindings.application_data.length = 4;

    input_chan_bindings.application_data.length = 0;
    input_chan_bindings.application_data.value = NULL;
#endif

    while(!context_established) {
	maj_stat =
	    gss_init_sec_context(&min_stat,
				 cred,
				 &context_hdl,
				 server,
				 mech_oid,
				 GSS_C_MUTUAL_FLAG | GSS_C_SEQUENCE_FLAG,
				 0,
				 NULL,
				 input_token,
				 NULL,
				 output_token,
				 NULL,
				 NULL);
	if (GSS_ERROR(maj_stat))
	    gss_err (1, min_stat, "gss_init_sec_context");
	if (output_token->length != 0)
	    write_token (sock, output_token);
	if (GSS_ERROR(maj_stat)) {
	    if (context_hdl != GSS_C_NO_CONTEXT)
		gss_delete_sec_context (&min_stat,
					&context_hdl,
					GSS_C_NO_BUFFER);
	    break;
	}
	if (maj_stat & GSS_S_CONTINUE_NEEDED) {
	    read_token (sock, input_token);
	} else {
	    context_established = 1;
	}

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
	    return do_trans (sock, context_hdl);
	}
    } else {
	return do_trans (sock, context_hdl);
    }
}