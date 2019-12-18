#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* backend_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_9__ {int enabled; int /*<<< orphan*/  opencl_platforms_version; int /*<<< orphan*/  opencl_platforms_vendor_id; int /*<<< orphan*/  opencl_platforms_vendor; int /*<<< orphan*/  opencl_platforms_name; int /*<<< orphan*/  opencl_platforms_devices_cnt; int /*<<< orphan*/  opencl_platforms_devices; int /*<<< orphan*/  opencl_platforms; scalar_t__ ocl; int /*<<< orphan*/  devices_param; } ;
typedef  TYPE_2__ backend_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  cuda_close (TYPE_1__*) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvrtc_close (TYPE_1__*) ; 
 int /*<<< orphan*/  ocl_close (TYPE_1__*) ; 

void backend_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (backend_ctx->enabled == false) return;

  hcfree (backend_ctx->devices_param);

  if (backend_ctx->ocl)
  {
    hcfree (backend_ctx->opencl_platforms);
    hcfree (backend_ctx->opencl_platforms_devices);
    hcfree (backend_ctx->opencl_platforms_devices_cnt);
    hcfree (backend_ctx->opencl_platforms_name);
    hcfree (backend_ctx->opencl_platforms_vendor);
    hcfree (backend_ctx->opencl_platforms_vendor_id);
    hcfree (backend_ctx->opencl_platforms_version);
  }

  nvrtc_close (hashcat_ctx);
  cuda_close  (hashcat_ctx);
  ocl_close   (hashcat_ctx);

  memset (backend_ctx, 0, sizeof (backend_ctx_t));
}