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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_realm ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_mk_error (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ make_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  send_reply (int,struct sockaddr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reply_error (krb5_realm realm,
	     int s,
	     struct sockaddr *sa,
	     int sa_size,
	     krb5_error_code error_code,
	     uint16_t result_code,
	     const char *expl)
{
    krb5_error_code ret;
    krb5_data error_data;
    krb5_data e_data;
    krb5_principal server = NULL;

    if (make_result(&e_data, result_code, expl))
	return;

    if (realm) {
	ret = krb5_make_principal (context, &server, realm,
				   "kadmin", "changepw", NULL);
	if (ret) {
	    krb5_data_free (&e_data);
	    return;
	}
    }

    ret = krb5_mk_error (context,
			 error_code,
			 NULL,
			 &e_data,
			 NULL,
			 server,
			 NULL,
			 NULL,
			 &error_data);
    if (server)
	krb5_free_principal(context, server);
    krb5_data_free (&e_data);
    if (ret) {
	krb5_warn (context, ret, "Could not even generate error reply");
	return;
    }
    send_reply (s, sa, sa_size, NULL, &error_data);
    krb5_data_free (&error_data);
}