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
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_KRB5_GET_SUBKEY_X ; 
 int /*<<< orphan*/  gsskrb5_extract_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

OM_uint32
gsskrb5_get_subkey(OM_uint32 *minor_status,
		   gss_ctx_id_t context_handle,
		   krb5_keyblock **keyblock)
{
    return gsskrb5_extract_key(minor_status,
			       context_handle,
			       GSS_KRB5_GET_SUBKEY_X,
			       keyblock);
}