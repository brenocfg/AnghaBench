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
typedef  TYPE_1__* gss_OID ;
struct TYPE_3__ {int length; } ;

/* Variables and functions */
 size_t der_length_len (size_t) ; 

void
_gssapi_encap_length (size_t data_len,
		      size_t *len,
		      size_t *total_len,
		      const gss_OID mech)
{
    size_t len_len;

    *len = 1 + 1 + mech->length + data_len;

    len_len = der_length_len(*len);

    *total_len = 1 + len_len + *len;
}