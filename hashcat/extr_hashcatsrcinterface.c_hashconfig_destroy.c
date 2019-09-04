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
typedef  int /*<<< orphan*/  module_ctx_t ;
typedef  int /*<<< orphan*/  hashconfig_t ;
struct TYPE_3__ {int /*<<< orphan*/ * module_ctx; int /*<<< orphan*/ * hashconfig; } ;
typedef  TYPE_1__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_unload (int /*<<< orphan*/ *) ; 

void hashconfig_destroy (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t *hashconfig = hashcat_ctx->hashconfig;
  module_ctx_t *module_ctx = hashcat_ctx->module_ctx;

  module_unload (module_ctx);

  memset (hashconfig, 0, sizeof (hashconfig_t));
}