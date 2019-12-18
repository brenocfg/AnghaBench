#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct digest_client_request_options {int /*<<< orphan*/ * password_string; int /*<<< orphan*/ * username_string; int /*<<< orphan*/ * client_nonce_string; int /*<<< orphan*/  type_string; int /*<<< orphan*/ * server_identifier_string; int /*<<< orphan*/ * server_nonce_string; int /*<<< orphan*/ * opaque_string; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  client_chap (char*,scalar_t__,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_mschapv2 (char*,scalar_t__,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* hex_decode (int /*<<< orphan*/ *,char*,int) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

int
digest_client_request(struct digest_client_request_options *opt,
		      int argc, char **argv)
{
    char *server_nonce, *client_nonce = NULL, server_identifier;
    ssize_t snoncelen, cnoncelen = 0;

    if (opt->server_nonce_string == NULL)
	errx(1, "server nonce missing");
    if (opt->password_string == NULL)
	errx(1, "password missing");

    if (opt->opaque_string == NULL)
	errx(1, "opaque missing");

    snoncelen = strlen(opt->server_nonce_string);
    server_nonce = malloc(snoncelen);
    if (server_nonce == NULL)
	errx(1, "server_nonce");

    snoncelen = hex_decode(opt->server_nonce_string, server_nonce, snoncelen);
    if (snoncelen <= 0)
	errx(1, "server nonce wrong");

    if (opt->client_nonce_string) {
	cnoncelen = strlen(opt->client_nonce_string);
	client_nonce = malloc(cnoncelen);
	if (client_nonce == NULL)
	    errx(1, "client_nonce");

	cnoncelen = hex_decode(opt->client_nonce_string,
			       client_nonce, cnoncelen);
	if (cnoncelen <= 0)
	    errx(1, "client nonce wrong");
    }

    if (opt->server_identifier_string) {
	int ret;

	ret = hex_decode(opt->server_identifier_string, &server_identifier, 1);
	if (ret != 1)
	    errx(1, "server identifier wrong length");
    }

    if (strcasecmp(opt->type_string, "CHAP") == 0) {
	if (opt->server_identifier_string == NULL)
	    errx(1, "server identifier missing");

	client_chap(server_nonce, snoncelen, server_identifier,
		    opt->password_string);

    } else if (strcasecmp(opt->type_string, "MS-CHAP-V2") == 0) {
	if (opt->client_nonce_string == NULL)
	    errx(1, "client nonce missing");
	if (opt->username_string == NULL)
	    errx(1, "client nonce missing");

	client_mschapv2(server_nonce, snoncelen,
			client_nonce, cnoncelen,
			opt->username_string,
			opt->password_string);
    }
    if (client_nonce)
	free(client_nonce);
    free(server_nonce);

    return 0;
}