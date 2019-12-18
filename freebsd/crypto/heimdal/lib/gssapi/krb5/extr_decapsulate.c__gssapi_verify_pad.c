#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int length; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_BAD_MECH ; 
 int /*<<< orphan*/  GSS_S_BAD_MIC ; 

OM_uint32
_gssapi_verify_pad(gss_buffer_t wrapped_token,
		   size_t datalen,
		   size_t *padlen)
{
    u_char *pad;
    size_t padlength;
    int i;

    pad = (u_char *)wrapped_token->value + wrapped_token->length - 1;
    padlength = *pad;

    if (padlength > datalen)
	return GSS_S_BAD_MECH;

    for (i = padlength; i > 0 && *pad == padlength; i--, pad--)
	;
    if (i != 0)
	return GSS_S_BAD_MIC;

    *padlen = padlength;

    return 0;
}