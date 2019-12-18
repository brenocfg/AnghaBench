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
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  asn1_TicketFlags_units () ; 
 int /*<<< orphan*/  client_principal ; 
 int /*<<< orphan*/ * client_principal_str ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  int2TicketFlags (int) ; 
 scalar_t__ keytab_file ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int parse_flags (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_flags_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_principal ; 
 int /*<<< orphan*/ * server_principal_str ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ticket_flags ; 
 scalar_t__ ticket_flags_str ; 

__attribute__((used)) static void
setup_env (krb5_context context, krb5_keytab *kt)
{
    krb5_error_code ret;

    if (keytab_file)
	ret = krb5_kt_resolve (context, keytab_file, kt);
    else
	ret = krb5_kt_default (context, kt);
    if (ret)
	krb5_err (context, 1, ret, "resolving keytab");

    if (client_principal_str == NULL)
	krb5_errx (context, 1, "missing client principal");
    ret = krb5_parse_name (context, client_principal_str, &client_principal);
    if (ret)
	krb5_err (context, 1, ret, "resolvning client name");

    if (server_principal_str == NULL)
	krb5_errx (context, 1, "missing server principal");
    ret = krb5_parse_name (context, server_principal_str, &server_principal);
    if (ret)
	krb5_err (context, 1, ret, "resolvning client name");

    if (ticket_flags_str) {
	int ticket_flags_int;

	ticket_flags_int = parse_flags(ticket_flags_str,
				       asn1_TicketFlags_units(), 0);
	if (ticket_flags_int <= 0) {
	    krb5_warnx (context, "bad ticket flags: `%s'", ticket_flags_str);
	    print_flags_table (asn1_TicketFlags_units(), stderr);
	    exit (1);
	}
	if (ticket_flags_int)
	    ticket_flags = int2TicketFlags (ticket_flags_int);
    }
}