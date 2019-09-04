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
typedef  int /*<<< orphan*/  user_options_extra_t ;
struct TYPE_3__ {int /*<<< orphan*/ * user_options_extra; } ;
typedef  TYPE_1__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void user_options_extra_destroy (hashcat_ctx_t *hashcat_ctx)
{
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  memset (user_options_extra, 0, sizeof (user_options_extra_t));
}