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
struct gssapi_data {int /*<<< orphan*/  delegated_cred_handle; int /*<<< orphan*/  context_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  use_kerberos ; 

__attribute__((used)) static int
gss_init(void *app_data)
{
    struct gssapi_data *d = app_data;
    d->context_hdl = GSS_C_NO_CONTEXT;
    d->delegated_cred_handle = GSS_C_NO_CREDENTIAL;
#if defined(FTP_SERVER)
    return 0;
#else
    /* XXX Check the gss mechanism; with  gss_indicate_mechs() ? */
#ifdef KRB5
    return !use_kerberos;
#else
    return 0;
#endif /* KRB5 */
#endif /* FTP_SERVER */
}