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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_auth_context ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_mk_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_mk_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ make_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  send_reply (int,struct sockaddr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reply_priv (krb5_auth_context auth_context,
	    int s,
	    struct sockaddr *sa,
	    int sa_size,
	    uint16_t result_code,
	    const char *expl)
{
    krb5_error_code ret;
    krb5_data krb_priv_data;
    krb5_data ap_rep_data;
    krb5_data e_data;

    ret = krb5_mk_rep (context,
		       auth_context,
		       &ap_rep_data);
    if (ret) {
	krb5_warn (context, ret, "Could not even generate error reply");
	return;
    }

    if (make_result(&e_data, result_code, expl))
	return;

    ret = krb5_mk_priv (context,
			auth_context,
			&e_data,
			&krb_priv_data,
			NULL);
    krb5_data_free (&e_data);
    if (ret) {
	krb5_warn (context, ret, "Could not even generate error reply");
	return;
    }
    send_reply (s, sa, sa_size, &ap_rep_data, &krb_priv_data);
    krb5_data_free (&ap_rep_data);
    krb5_data_free (&krb_priv_data);
}