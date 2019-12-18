#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* gsskrb5_cred ;
typedef  scalar_t__ gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_2__ {int /*<<< orphan*/  cred_flags; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_CF_NO_CI_FLAGS ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 

__attribute__((used)) static OM_uint32
no_ci_flags(OM_uint32 *minor_status,
	    krb5_context context,
	    gss_cred_id_t *cred_handle,
	    const gss_buffer_t value)
{
    gsskrb5_cred cred;

    if (cred_handle == NULL || *cred_handle == GSS_C_NO_CREDENTIAL) {
	*minor_status = 0;
	return GSS_S_FAILURE;
    }

    cred = (gsskrb5_cred)*cred_handle;
    cred->cred_flags |= GSS_CF_NO_CI_FLAGS;

    *minor_status = 0;
    return GSS_S_COMPLETE;

}