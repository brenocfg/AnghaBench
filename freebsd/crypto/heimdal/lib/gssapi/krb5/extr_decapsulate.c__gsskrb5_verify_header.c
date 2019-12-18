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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_DEFECTIVE_TOKEN ; 
 scalar_t__ _gssapi_verify_mech_header (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ct_memcmp (int /*<<< orphan*/ *,void const*,int) ; 

OM_uint32
_gsskrb5_verify_header(u_char **str,
			  size_t total_len,
			  const void *type,
			  gss_OID oid)
{
    OM_uint32 ret;
    size_t len;
    u_char *p = *str;

    ret = _gssapi_verify_mech_header(str, total_len, oid);
    if (ret)
	return ret;

    len = total_len - (*str - p);

    if (len < 2)
	return GSS_S_DEFECTIVE_TOKEN;

    if (ct_memcmp (*str, type, 2) != 0)
	return GSS_S_DEFECTIVE_TOKEN;
    *str += 2;

    return 0;
}