#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* backend_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/ * ocl; } ;
typedef  TYPE_2__ backend_ctx_t ;
struct TYPE_7__ {scalar_t__ lib; } ;
typedef  TYPE_3__ OCL_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  hc_dlclose (scalar_t__) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ *) ; 

void ocl_close (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  OCL_PTR *ocl = (OCL_PTR *) backend_ctx->ocl;

  if (ocl)
  {
    if (ocl->lib)
    {
      hc_dlclose (ocl->lib);
    }

    hcfree (backend_ctx->ocl);

    backend_ctx->ocl = NULL;
  }
}