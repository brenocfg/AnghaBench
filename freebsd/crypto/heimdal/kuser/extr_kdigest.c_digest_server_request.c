#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct digest_server_request_options {int /*<<< orphan*/  kerberos_realm_string; int /*<<< orphan*/ * client_response_string; int /*<<< orphan*/ * opaque_string; int /*<<< orphan*/  client_nonce_string; int /*<<< orphan*/ * server_nonce_string; int /*<<< orphan*/  username_string; int /*<<< orphan*/ * type_string; int /*<<< orphan*/ * server_identifier_string; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_digest ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hex_encode (int /*<<< orphan*/ ,scalar_t__,char**) ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 scalar_t__ krb5_digest_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_digest_free (int /*<<< orphan*/ ) ; 
 char* krb5_digest_get_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_digest_get_session_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_digest_rep_get_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_digest_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_digest_set_client_nonce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_digest_set_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_digest_set_opaque (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_digest_set_responseData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_digest_set_server_nonce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_digest_set_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_digest_set_username (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

int
digest_server_request(struct digest_server_request_options *opt,
		      int argc, char **argv)
{
    krb5_error_code ret;
    krb5_digest digest;
    const char *status, *rsp;
    krb5_data session_key;

    if (opt->server_nonce_string == NULL)
	errx(1, "server nonce missing");
    if (opt->type_string == NULL)
	errx(1, "type missing");
    if (opt->opaque_string == NULL)
	errx(1, "opaque missing");
    if (opt->client_response_string == NULL)
	errx(1, "client response missing");

    ret = krb5_digest_alloc(context, &digest);
    if (ret)
	krb5_err(context, 1, ret, "digest_alloc");

    if (strcasecmp(opt->type_string, "CHAP") == 0) {
	if (opt->server_identifier_string == NULL)
	    errx(1, "server identifier missing");

	ret = krb5_digest_set_identifier(context, digest,
					 opt->server_identifier_string);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_digest_set_type");
    }

    ret = krb5_digest_set_type(context, digest, opt->type_string);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_set_type");

    ret = krb5_digest_set_username(context, digest, opt->username_string);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_set_username");

    ret = krb5_digest_set_server_nonce(context, digest,
				       opt->server_nonce_string);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_set_server_nonce");

    if(opt->client_nonce_string) {
	ret = krb5_digest_set_client_nonce(context, digest,
					   opt->client_nonce_string);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_digest_set_client_nonce");
    }


    ret = krb5_digest_set_opaque(context, digest, opt->opaque_string);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_set_opaque");

    ret = krb5_digest_set_responseData(context, digest,
				       opt->client_response_string);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_set_responseData");

    ret = krb5_digest_request(context, digest,
			      opt->kerberos_realm_string, id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_request");

    status = krb5_digest_rep_get_status(context, digest) ? "ok" : "failed";
    rsp = krb5_digest_get_rsp(context, digest);

    printf("status=%s\n", status);
    if (rsp)
	printf("rsp=%s\n", rsp);
    printf("tickets=no\n");

    ret = krb5_digest_get_session_key(context, digest, &session_key);
    if (ret)
	krb5_err(context, 1, ret, "krb5_digest_get_session_key");

    if (session_key.length) {
	char *key;
	hex_encode(session_key.data, session_key.length, &key);
	if (key == NULL)
	    krb5_errx(context, 1, "hex_encode");
	krb5_data_free(&session_key);
	printf("session-key=%s\n", key);
	free(key);
    }

    krb5_digest_free(digest);

    return 0;
}