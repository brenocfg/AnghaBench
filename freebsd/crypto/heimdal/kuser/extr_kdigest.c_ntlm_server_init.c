#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type2 ;
struct TYPE_6__ {char* data; int length; } ;
struct ntlm_type2 {char* targetname; TYPE_1__ targetinfo; int /*<<< orphan*/  flags; int /*<<< orphan*/  challenge; } ;
struct ntlm_server_init_options {int /*<<< orphan*/  kerberos_realm_string; } ;
struct ntlm_buf {char* data; int length; } ;
typedef  int /*<<< orphan*/  krb5_ntlm ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_7__ {int length; char* data; } ;
typedef  TYPE_2__ krb5_data ;

/* Variables and functions */
 int NTLM_NEG_NTLM ; 
 int NTLM_NEG_UNICODE ; 
 int /*<<< orphan*/  base64_encode (char*,int,char**) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ heim_ntlm_encode_type2 (struct ntlm_type2*,struct ntlm_buf*) ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ krb5_ntlm_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_ntlm_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ntlm_init_get_challange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ krb5_ntlm_init_get_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ntlm_init_get_opaque (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_ntlm_init_get_targetname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_ntlm_init_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct ntlm_type2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
ntlm_server_init(struct ntlm_server_init_options *opt,
		 int argc, char ** argv)
{
    krb5_error_code ret;
    krb5_ntlm ntlm;
    struct ntlm_type2 type2;
    krb5_data challenge, opaque;
    struct ntlm_buf data;
    char *s;
    static char zero2[] = "\x00\x00";

    memset(&type2, 0, sizeof(type2));

    ret = krb5_ntlm_alloc(context, &ntlm);
    if (ret)
	krb5_err(context, 1, ret, "krb5_ntlm_alloc");

    ret = krb5_ntlm_init_request(context,
				 ntlm,
				 opt->kerberos_realm_string,
				 id,
				 NTLM_NEG_UNICODE|NTLM_NEG_NTLM,
				 "NUTCRACKER",
				 "L");
    if (ret)
	krb5_err(context, 1, ret, "krb5_ntlm_init_request");

    /*
     *
     */

    ret = krb5_ntlm_init_get_challange(context, ntlm, &challenge);
    if (ret)
	krb5_err(context, 1, ret, "krb5_ntlm_init_get_challange");

    if (challenge.length != sizeof(type2.challenge))
	krb5_errx(context, 1, "ntlm challenge have wrong length");
    memcpy(type2.challenge, challenge.data, sizeof(type2.challenge));
    krb5_data_free(&challenge);

    ret = krb5_ntlm_init_get_flags(context, ntlm, &type2.flags);
    if (ret)
	krb5_err(context, 1, ret, "krb5_ntlm_init_get_flags");

    krb5_ntlm_init_get_targetname(context, ntlm, &type2.targetname);
    type2.targetinfo.data = zero2;
    type2.targetinfo.length = 2;

    ret = heim_ntlm_encode_type2(&type2, &data);
    if (ret)
	krb5_errx(context, 1, "heim_ntlm_encode_type2");

    free(type2.targetname);

    /*
     *
     */

    base64_encode(data.data, data.length, &s);
    free(data.data);
    printf("type2=%s\n", s);
    free(s);

    /*
     *
     */

    ret = krb5_ntlm_init_get_opaque(context, ntlm, &opaque);
    if (ret)
	krb5_err(context, 1, ret, "krb5_ntlm_init_get_opaque");

    base64_encode(opaque.data, opaque.length, &s);
    krb5_data_free(&opaque);
    printf("opaque=%s\n", s);
    free(s);

    /*
     *
     */

    krb5_ntlm_free(context, ntlm);

    return 0;
}