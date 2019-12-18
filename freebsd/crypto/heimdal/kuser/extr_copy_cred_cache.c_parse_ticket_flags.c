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
struct TYPE_6__ {int i; } ;
typedef  TYPE_1__ krb5_ticket_flags ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  ff ;
struct TYPE_7__ {int proxy; } ;
typedef  TYPE_2__ TicketFlags ;

/* Variables and functions */
 size_t TicketFlags2int (TYPE_2__) ; 
 int /*<<< orphan*/  asn1_TicketFlags_units () ; 
 int bitswap32 (int) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int parse_flags (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_ticket_flags(krb5_context context,
		   const char *string, krb5_ticket_flags *ret_flags)
{
    TicketFlags ff;
    int flags = parse_flags(string, asn1_TicketFlags_units(), 0);
    if (flags == -1)	/* XXX */
	krb5_errx(context, 1, "bad flags specified: \"%s\"", string);

    memset(&ff, 0, sizeof(ff));
    ff.proxy = 1;
    if ((size_t)parse_flags("proxy", asn1_TicketFlags_units(), 0) == TicketFlags2int(ff))
	ret_flags->i = flags;
    else
	ret_flags->i = bitswap32(flags);
}