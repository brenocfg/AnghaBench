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
typedef  int u_char ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int OM_uint32 ;

/* Variables and functions */

krb5_error_code
_gsskrb5_decode_om_uint32(const void *ptr, OM_uint32 *n)
{
    const u_char *p = ptr;
    *n = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
    return 0;
}