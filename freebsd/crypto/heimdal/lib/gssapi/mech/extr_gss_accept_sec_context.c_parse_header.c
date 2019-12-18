#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_buffer_t ;
typedef  TYPE_2__* gss_OID ;
struct TYPE_6__ {unsigned char length; unsigned char* elements; } ;
struct TYPE_5__ {unsigned char* value; size_t length; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_DEFECTIVE_TOKEN ; 

__attribute__((used)) static OM_uint32
parse_header(const gss_buffer_t input_token, gss_OID mech_oid)
{
	unsigned char *p = input_token->value;
	size_t len = input_token->length;
	size_t a, b;

	/*
	 * Token must start with [APPLICATION 0] SEQUENCE.
	 * But if it doesn't assume it is DCE-STYLE Kerberos!
	 */
	if (len == 0)
		return (GSS_S_DEFECTIVE_TOKEN);

	p++;
	len--;

	/*
	 * Decode the length and make sure it agrees with the
	 * token length.
	 */
	if (len == 0)
		return (GSS_S_DEFECTIVE_TOKEN);
	if ((*p & 0x80) == 0) {
		a = *p;
		p++;
		len--;
	} else {
		b = *p & 0x7f;
		p++;
		len--;
		if (len < b)
		    return (GSS_S_DEFECTIVE_TOKEN);
		a = 0;
		while (b) {
		    a = (a << 8) | *p;
		    p++;
		    len--;
		    b--;
		}
	}
	if (a != len)
		return (GSS_S_DEFECTIVE_TOKEN);

	/*
	 * Decode the OID for the mechanism. Simplify life by
	 * assuming that the OID length is less than 128 bytes.
	 */
	if (len < 2 || *p != 0x06)
		return (GSS_S_DEFECTIVE_TOKEN);
	if ((p[1] & 0x80) || p[1] > (len - 2))
		return (GSS_S_DEFECTIVE_TOKEN);
	mech_oid->length = p[1];
	p += 2;
	len -= 2;
	mech_oid->elements = p;

	return GSS_S_COMPLETE;
}