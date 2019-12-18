#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rp_files; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_5__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 

void user_options_destroy (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  hcfree (user_options->rp_files);

  //do not reset this, it might be used from main.c
  //memset (user_options, 0, sizeof (user_options_t));
}