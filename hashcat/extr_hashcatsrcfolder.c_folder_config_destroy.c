#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* folder_config; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  install_dir; int /*<<< orphan*/  cwd; int /*<<< orphan*/  cpath_real; } ;
typedef  TYPE_2__ folder_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void folder_config_destroy (hashcat_ctx_t *hashcat_ctx)
{
  folder_config_t *folder_config = hashcat_ctx->folder_config;

  hcfree (folder_config->cpath_real);
  hcfree (folder_config->cwd);
  hcfree (folder_config->install_dir);

  memset (folder_config, 0, sizeof (folder_config_t));
}