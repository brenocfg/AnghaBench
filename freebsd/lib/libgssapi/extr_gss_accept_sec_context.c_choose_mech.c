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
typedef  TYPE_1__* gss_buffer_t ;
typedef  int /*<<< orphan*/ * gss_OID ;
struct TYPE_4__ {int length; scalar_t__ value; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  krb5_mechanism ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  ntlm_mechanism ; 
 scalar_t__ parse_header (TYPE_1__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spnego_mechanism ; 

__attribute__((used)) static OM_uint32
choose_mech(const gss_buffer_t input, gss_OID mech_oid)
{
	OM_uint32 status;

	/*
	 * First try to parse the gssapi token header and see if it's a
	 * correct header, use that in the first hand.
	 */

	status = parse_header(input, mech_oid);
	if (status == GSS_S_COMPLETE)
		return (GSS_S_COMPLETE);
    
	/*
	 * Lets guess what mech is really is, callback function to mech ??
	 */

	if (input->length > 8 && 
	    memcmp((const char *)input->value, "NTLMSSP\x00", 8) == 0)
	{
		*mech_oid = ntlm_mechanism;
		return (GSS_S_COMPLETE);
	} else if (input->length != 0 &&
	    ((const char *)input->value)[0] == 0x6E)
	{
		/* Could be a raw AP-REQ (check for APPLICATION tag) */
		*mech_oid = krb5_mechanism;
		return (GSS_S_COMPLETE);
	} else if (input->length == 0) {
		/* 
		 * There is the a weird mode of SPNEGO (in CIFS and
		 * SASL GSS-SPENGO where the first token is zero
		 * length and the acceptor returns a mech_list, lets
		 * hope that is what is happening now.
		 */
		*mech_oid = spnego_mechanism;
		return (GSS_S_COMPLETE);
	}
	return (status);
}