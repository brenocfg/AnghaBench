#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ krb5_timestamp ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_19__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_13__ {scalar_t__ renewable; } ;
struct TYPE_18__ {TYPE_12__ b; } ;
struct TYPE_17__ {scalar_t__ authtime; scalar_t__ starttime; scalar_t__ endtime; scalar_t__ renew_till; } ;
struct TYPE_16__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {scalar_t__ keytype; } ;
struct TYPE_20__ {TYPE_6__ addresses; TYPE_5__ flags; TYPE_4__ times; TYPE_3__ ticket; TYPE_2__ session; int /*<<< orphan*/  client; int /*<<< orphan*/  server; } ;
typedef  TYPE_7__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_14__ {int etype; int* kvno; } ;
struct TYPE_21__ {TYPE_1__ enc_part; } ;
typedef  TYPE_8__ Ticket ;

/* Variables and functions */
 char* N_ (char*,char*) ; 
 int /*<<< orphan*/  TicketFlags2int (TYPE_12__) ; 
 int /*<<< orphan*/  asn1_TicketFlags_units () ; 
 int /*<<< orphan*/  decode_Ticket (int /*<<< orphan*/ ,scalar_t__,TYPE_8__*,size_t*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_Ticket (TYPE_8__*) ; 
 scalar_t__ krb5_enctype_to_string (int /*<<< orphan*/ ,int,char**) ; 
 scalar_t__ krb5_print_address (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  krb5_timeofday (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 char* printable_time_long (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  unparse_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_cred_verbose(krb5_context context, krb5_creds *cred)
{
    size_t j;
    char *str;
    krb5_error_code ret;
    krb5_timestamp sec;

    krb5_timeofday (context, &sec);

    ret = krb5_unparse_name(context, cred->server, &str);
    if(ret)
	exit(1);
    printf(N_("Server: %s\n", ""), str);
    free (str);

    ret = krb5_unparse_name(context, cred->client, &str);
    if(ret)
	exit(1);
    printf(N_("Client: %s\n", ""), str);
    free (str);

    {
	Ticket t;
	size_t len;
	char *s;

	decode_Ticket(cred->ticket.data, cred->ticket.length, &t, &len);
	ret = krb5_enctype_to_string(context, t.enc_part.etype, &s);
	printf(N_("Ticket etype: ", ""));
	if (ret == 0) {
	    printf("%s", s);
	    free(s);
	} else {
	    printf(N_("unknown-enctype(%d)", ""), t.enc_part.etype);
	}
	if(t.enc_part.kvno)
	    printf(N_(", kvno %d", ""), *t.enc_part.kvno);
	printf("\n");
	if(cred->session.keytype != t.enc_part.etype) {
	    ret = krb5_enctype_to_string(context, cred->session.keytype, &str);
	    if(ret)
		krb5_warn(context, ret, "session keytype");
	    else {
		printf(N_("Session key: %s\n", "enctype"), str);
		free(str);
	    }
	}
	free_Ticket(&t);
	printf(N_("Ticket length: %lu\n", ""),
	       (unsigned long)cred->ticket.length);
    }
    printf(N_("Auth time:  %s\n", ""),
	   printable_time_long(cred->times.authtime));
    if(cred->times.authtime != cred->times.starttime)
	printf(N_("Start time: %s\n", ""),
	       printable_time_long(cred->times.starttime));
    printf(N_("End time:   %s", ""),
	   printable_time_long(cred->times.endtime));
    if(sec > cred->times.endtime)
	printf(N_(" (expired)", ""));
    printf("\n");
    if(cred->flags.b.renewable)
	printf(N_("Renew till: %s\n", ""),
	       printable_time_long(cred->times.renew_till));
    {
	char flags[1024];
	unparse_flags(TicketFlags2int(cred->flags.b),
		      asn1_TicketFlags_units(),
		      flags, sizeof(flags));
	printf(N_("Ticket flags: %s\n", ""), flags);
    }
    printf(N_("Addresses: ", ""));
    if (cred->addresses.len != 0) {
	for(j = 0; j < cred->addresses.len; j++){
	    char buf[128];
	    size_t len;
	    if(j) printf(", ");
	    ret = krb5_print_address(&cred->addresses.val[j],
				     buf, sizeof(buf), &len);

	    if(ret == 0)
		printf("%s", buf);
	}
    } else {
	printf(N_("addressless", ""));
    }
    printf("\n\n");
}