#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int enabled; int /*<<< orphan*/  platforms_skipped; int /*<<< orphan*/  platforms_version; int /*<<< orphan*/  platforms_name; int /*<<< orphan*/  platforms_vendor; int /*<<< orphan*/  platform_devices; int /*<<< orphan*/  platforms; int /*<<< orphan*/  devices_param; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_7__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocl_close (TYPE_2__*) ; 

void opencl_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (opencl_ctx->enabled == false) return;

  ocl_close (hashcat_ctx);

  hcfree (opencl_ctx->devices_param);

  hcfree (opencl_ctx->platforms);
  hcfree (opencl_ctx->platform_devices);
  hcfree (opencl_ctx->platforms_vendor);
  hcfree (opencl_ctx->platforms_name);
  hcfree (opencl_ctx->platforms_version);
  hcfree (opencl_ctx->platforms_skipped);

  memset (opencl_ctx, 0, sizeof (opencl_ctx_t));
}