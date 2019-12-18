#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  remote ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_12__ {scalar_t__ length; char* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int GSS_C_MUTUAL_FLAG ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 int /*<<< orphan*/  GSS_C_NO_CHANNEL_BINDINGS ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 int /*<<< orphan*/  GSS_C_NT_HOSTBASED_SERVICE ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int GSS_C_SEQUENCE_FLAG ; 
 scalar_t__ GSS_ERROR (int) ; 
 int GSS_S_CONTINUE_NEEDED ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_err (int,int,char*,...) ; 
 int gss_get_mic (int*,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int gss_import_name (int*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gss_init_sec_context (int*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gss_wrap (int*,scalar_t__,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nt_read_token (int,TYPE_1__*) ; 
 int /*<<< orphan*/  nt_write_token (int,TYPE_1__*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int
proto (int sock, const char *hostname, const char *service)
{
    struct sockaddr_in remote, local;
    socklen_t addrlen;

    int context_established = 0;
    gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
    gss_buffer_t input_token, output_token;
    gss_buffer_desc real_input_token, real_output_token;
    OM_uint32 maj_stat, min_stat;
    gss_name_t server;
    gss_buffer_desc name_token;
    char *str;

    name_token.length = asprintf (&str,
				  "%s@%s", service, hostname);
    if (str == NULL)
	errx(1, "out of memory");
    name_token.value = str;

    maj_stat = gss_import_name (&min_stat,
				&name_token,
				GSS_C_NT_HOSTBASED_SERVICE,
				&server);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat,
		 "Error importing name `%s@%s':\n", service, hostname);

    addrlen = sizeof(local);
    if (getsockname (sock, (struct sockaddr *)&local, &addrlen) < 0
	|| addrlen != sizeof(local))
	err (1, "getsockname(%s)", hostname);

    addrlen = sizeof(remote);
    if (getpeername (sock, (struct sockaddr *)&remote, &addrlen) < 0
	|| addrlen != sizeof(remote))
	err (1, "getpeername(%s)", hostname);

    input_token = &real_input_token;
    output_token = &real_output_token;

    input_token->length = 0;
    output_token->length = 0;

    while(!context_established) {
	maj_stat =
	    gss_init_sec_context(&min_stat,
				 GSS_C_NO_CREDENTIAL,
				 &context_hdl,
				 server,
				 GSS_C_NO_OID,
				 GSS_C_MUTUAL_FLAG | GSS_C_SEQUENCE_FLAG,
				 0,
				 GSS_C_NO_CHANNEL_BINDINGS,
				 input_token,
				 NULL,
				 output_token,
				 NULL,
				 NULL);
	if (GSS_ERROR(maj_stat))
	    gss_err (1, min_stat, "gss_init_sec_context");
	if (output_token->length != 0)
	    nt_write_token (sock, output_token);
	if (GSS_ERROR(maj_stat)) {
	    if (context_hdl != GSS_C_NO_CONTEXT)
		gss_delete_sec_context (&min_stat,
					&context_hdl,
					GSS_C_NO_BUFFER);
	    break;
	}
	if (maj_stat & GSS_S_CONTINUE_NEEDED) {
	    nt_read_token (sock, input_token);
	} else {
	    context_established = 1;
	}

    }

    /* get_mic */

    input_token->length = 3;
    input_token->value  = strdup("hej");

    maj_stat = gss_get_mic(&min_stat,
			   context_hdl,
			   GSS_C_QOP_DEFAULT,
			   input_token,
			   output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_get_mic");

    nt_write_token (sock, input_token);
    nt_write_token (sock, output_token);

    /* wrap */

    input_token->length = 7;
    input_token->value  = "hemligt";


    maj_stat = gss_wrap (&min_stat,
			 context_hdl,
			 1,
			 GSS_C_QOP_DEFAULT,
			 input_token,
			 NULL,
			 output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_wrap");

    nt_write_token (sock, output_token);

    return 0;
}