#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
typedef  int /*<<< orphan*/  sbuf ;
typedef  scalar_t__ gss_name_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  scalar_t__ gss_cred_id_t ;
struct TYPE_21__ {char* value; int length; } ;
typedef  TYPE_1__ gss_buffer_desc ;
struct TYPE_22__ {int count; TYPE_3__* elements; } ;
typedef  TYPE_2__ gss_OID_set_desc ;
struct TYPE_23__ {int member_0; void* member_1; } ;
typedef  TYPE_3__ gss_OID_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  enctype ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int ETYPE_DES_CBC_CRC ; 
 int /*<<< orphan*/  GSS_C_ACCEPT ; 
 int GSS_C_CONF_FLAG ; 
 int /*<<< orphan*/  GSS_C_INITIATE ; 
 int GSS_C_INTEG_FLAG ; 
 int GSS_C_MUTUAL_FLAG ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 int /*<<< orphan*/  GSS_C_NO_CHANNEL_BINDINGS ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 scalar_t__ GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_C_NO_OID ; 
 TYPE_2__* GSS_C_NO_OID_SET ; 
 int /*<<< orphan*/  GSS_C_NT_HOSTBASED_SERVICE ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 scalar_t__ GSS_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  GSS_KRB5_SET_ALLOWABLE_ENCTYPES_X ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  getcredhostname (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ gss_accept_sec_context (scalar_t__*,scalar_t__*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_acquire_cred (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_delete_sec_context (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gss_get_mic (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ gss_import_name (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ gss_init_sec_context (scalar_t__*,scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_cred (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gss_release_name (scalar_t__*,scalar_t__*) ; 
 scalar_t__ gss_set_cred_option (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ gss_unwrap (scalar_t__*,scalar_t__,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_verify_mic (scalar_t__*,scalar_t__,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_wrap (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_error (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 void* strlen (char const*) ; 

__attribute__((used)) static int
gsstest_1(struct thread *td)
{
	OM_uint32 maj_stat, min_stat;
	OM_uint32 smaj_stat, smin_stat;
	int context_established = 0;
	gss_ctx_id_t client_context = GSS_C_NO_CONTEXT;
	gss_ctx_id_t server_context = GSS_C_NO_CONTEXT;
	gss_cred_id_t client_cred = GSS_C_NO_CREDENTIAL;
	gss_cred_id_t server_cred = GSS_C_NO_CREDENTIAL;
	gss_name_t name = GSS_C_NO_NAME;
	gss_name_t received_name = GSS_C_NO_NAME;
	gss_buffer_desc name_desc;
	gss_buffer_desc client_token, server_token, message_buf;
	gss_OID mech, actual_mech, mech_type;
	static gss_OID_desc krb5_desc =
		{9, (void *)"\x2a\x86\x48\x86\xf7\x12\x01\x02\x02"};
#if 0
	static gss_OID_desc spnego_desc =
		{6, (void *)"\x2b\x06\x01\x05\x05\x02"};
	static gss_OID_desc ntlm_desc =
		{10, (void *)"\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a"};
#endif
	char enctype[sizeof(uint32_t)];

	mech = GSS_C_NO_OID;

	{
		static char sbuf[512];
		memcpy(sbuf, "nfs@", 4);
		getcredhostname(td->td_ucred, sbuf + 4, sizeof(sbuf) - 4);
		name_desc.value = sbuf;
	}

	name_desc.length = strlen((const char *) name_desc.value);
	maj_stat = gss_import_name(&min_stat, &name_desc,
	    GSS_C_NT_HOSTBASED_SERVICE, &name);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_import_name failed\n");
		report_error(mech, maj_stat, min_stat);
		goto out;
	}

	maj_stat = gss_acquire_cred(&min_stat, GSS_C_NO_NAME,
	    0, GSS_C_NO_OID_SET, GSS_C_INITIATE, &client_cred,
	    NULL, NULL);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_acquire_cred (client) failed\n");
		report_error(mech, maj_stat, min_stat);
		goto out;
	}

	enctype[0] = (ETYPE_DES_CBC_CRC >> 24) & 0xff;
	enctype[1] = (ETYPE_DES_CBC_CRC >> 16) & 0xff;
	enctype[2] = (ETYPE_DES_CBC_CRC >> 8) & 0xff;
	enctype[3] = ETYPE_DES_CBC_CRC & 0xff;
	message_buf.length = sizeof(enctype);
	message_buf.value = enctype;
	maj_stat = gss_set_cred_option(&min_stat, &client_cred,
	    GSS_KRB5_SET_ALLOWABLE_ENCTYPES_X, &message_buf);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_set_cred_option failed\n");
		report_error(mech, maj_stat, min_stat);
		goto out;
	}

	server_token.length = 0;
	server_token.value = NULL;
	while (!context_established) {
		client_token.length = 0;
		client_token.value = NULL;
		maj_stat = gss_init_sec_context(&min_stat,
		    client_cred,
		    &client_context,
		    name,
		    mech,
		    GSS_C_MUTUAL_FLAG|GSS_C_CONF_FLAG|GSS_C_INTEG_FLAG,
		    0,
		    GSS_C_NO_CHANNEL_BINDINGS,
		    &server_token,
		    &actual_mech,
		    &client_token,
		    NULL,
		    NULL);
		if (server_token.length)
			gss_release_buffer(&smin_stat, &server_token);
		if (GSS_ERROR(maj_stat)) {
			printf("gss_init_sec_context failed\n");
			report_error(mech, maj_stat, min_stat);
			goto out;
		}

		if (client_token.length != 0) {
			if (!server_cred) {
				gss_OID_set_desc oid_set;
				oid_set.count = 1;
				oid_set.elements = &krb5_desc;
				smaj_stat = gss_acquire_cred(&smin_stat,
				    name, 0, &oid_set, GSS_C_ACCEPT, &server_cred,
				    NULL, NULL);
				if (GSS_ERROR(smaj_stat)) {
					printf("gss_acquire_cred (server) failed\n");
					report_error(mech_type, smaj_stat, smin_stat);
					goto out;
				}
			}
			smaj_stat = gss_accept_sec_context(&smin_stat,
			    &server_context,
			    server_cred,
			    &client_token,
			    GSS_C_NO_CHANNEL_BINDINGS,
			    &received_name,
			    &mech_type,
			    &server_token,
			    NULL,
			    NULL,
			    NULL);
			if (GSS_ERROR(smaj_stat)) {
				printf("gss_accept_sec_context failed\n");
				report_error(mech_type, smaj_stat, smin_stat);
				goto out;
			}
			gss_release_buffer(&min_stat, &client_token);
		}
		if (GSS_ERROR(maj_stat)) {
			if (client_context != GSS_C_NO_CONTEXT)
				gss_delete_sec_context(&min_stat,
				    &client_context,
				    GSS_C_NO_BUFFER);
			break;
		}

		if (maj_stat == GSS_S_COMPLETE) {
			context_established = 1;
		}
	}

	message_buf.length = strlen("Hello world");
	message_buf.value = (void *) "Hello world";

	maj_stat = gss_get_mic(&min_stat, client_context,
	    GSS_C_QOP_DEFAULT, &message_buf, &client_token);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_get_mic failed\n");
		report_error(mech_type, maj_stat, min_stat);
		goto out;
	}
	maj_stat = gss_verify_mic(&min_stat, server_context,
	    &message_buf, &client_token, NULL);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_verify_mic failed\n");
		report_error(mech_type, maj_stat, min_stat);
		goto out;
	}
	gss_release_buffer(&min_stat, &client_token);

	maj_stat = gss_wrap(&min_stat, client_context,
	    TRUE, GSS_C_QOP_DEFAULT, &message_buf, NULL, &client_token);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_wrap failed\n");
		report_error(mech_type, maj_stat, min_stat);
		goto out;
	}
	maj_stat = gss_unwrap(&min_stat, server_context,
	    &client_token, &server_token, NULL, NULL);
	if (GSS_ERROR(maj_stat)) {
		printf("gss_unwrap failed\n");
		report_error(mech_type, maj_stat, min_stat);
		goto out;
	}

 	if (message_buf.length != server_token.length
	    || memcmp(message_buf.value, server_token.value,
		message_buf.length))
		printf("unwrap result corrupt\n");
	
	gss_release_buffer(&min_stat, &client_token);
	gss_release_buffer(&min_stat, &server_token);

out:
	if (client_context)
		gss_delete_sec_context(&min_stat, &client_context,
		    GSS_C_NO_BUFFER);
	if (server_context)
		gss_delete_sec_context(&min_stat, &server_context,
		    GSS_C_NO_BUFFER);
	if (client_cred)
		gss_release_cred(&min_stat, &client_cred);
	if (server_cred)
		gss_release_cred(&min_stat, &server_cred);
	if (name)
		gss_release_name(&min_stat, &name);
	if (received_name)
		gss_release_name(&min_stat, &received_name);

	return (0);
}