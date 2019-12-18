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
typedef  void u_char ;
typedef  int /*<<< orphan*/  gss_OID ;

/* Variables and functions */
 void* _gssapi_make_mech_header (void*,size_t,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

void *
_gsskrb5_make_header (void *ptr,
			 size_t len,
			 const void *type,
			 const gss_OID mech)
{
    u_char *p = ptr;
    p = _gssapi_make_mech_header(p, len, mech);
    memcpy (p, type, 2);
    p += 2;
    return p;
}