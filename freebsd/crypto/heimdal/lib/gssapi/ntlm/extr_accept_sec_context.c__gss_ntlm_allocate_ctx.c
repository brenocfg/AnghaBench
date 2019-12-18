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
struct ntlm_server_interface {scalar_t__ (* nsi_init ) (scalar_t__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* ntlm_ctx ;
struct TYPE_4__ {int /*<<< orphan*/  ictx; struct ntlm_server_interface* server; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 TYPE_1__* calloc (int,int) ; 
 struct ntlm_server_interface ntlmsspi_kdc_digest ; 
 scalar_t__ stub1 (scalar_t__*,int /*<<< orphan*/ *) ; 

OM_uint32
_gss_ntlm_allocate_ctx(OM_uint32 *minor_status, ntlm_ctx *ctx)
{
    OM_uint32 maj_stat;
    struct ntlm_server_interface *ns_interface = NULL;

#ifdef DIGEST
    ns_interface = &ntlmsspi_kdc_digest;
#endif
    if (ns_interface == NULL)
	return GSS_S_FAILURE;

    *ctx = calloc(1, sizeof(**ctx));

    (*ctx)->server = ns_interface;

    maj_stat = (*(*ctx)->server->nsi_init)(minor_status, &(*ctx)->ictx);
    if (maj_stat != GSS_S_COMPLETE)
	return maj_stat;

    return GSS_S_COMPLETE;
}