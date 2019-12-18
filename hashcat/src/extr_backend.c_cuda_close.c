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
struct TYPE_6__ {int /*<<< orphan*/ * cuda; } ;
typedef  TYPE_2__ backend_ctx_t ;
struct TYPE_7__ {scalar_t__ lib; } ;
typedef  TYPE_3__ CUDA_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  hc_dlclose (scalar_t__) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ *) ; 

void cuda_close (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  CUDA_PTR *cuda = (CUDA_PTR *) backend_ctx->cuda;

  if (cuda)
  {
    if (cuda->lib)
    {
      hc_dlclose (cuda->lib);
    }

    hcfree (backend_ctx->cuda);

    backend_ctx->cuda = NULL;
  }
}