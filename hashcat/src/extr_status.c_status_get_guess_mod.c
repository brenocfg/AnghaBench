#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ attack_mode; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_10__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_2__ straight_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  mask; } ;
typedef  TYPE_3__ mask_ctx_t ;
struct TYPE_12__ {int opti_type; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_13__ {TYPE_3__* mask_ctx; TYPE_2__* straight_ctx; TYPE_6__* combinator_ctx; TYPE_1__* user_options; TYPE_4__* hashconfig; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_14__ {scalar_t__ combs_mode; int /*<<< orphan*/  dict1; int /*<<< orphan*/  dict2; } ;
typedef  TYPE_6__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ COMBINATOR_MODE_BASE_LEFT ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 char* status_get_rules_file (TYPE_5__ const*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

char *status_get_guess_mod (const hashcat_ctx_t *hashcat_ctx)
{
  const hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    return status_get_rules_file (hashcat_ctx);
  }

  if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    const combinator_ctx_t *combinator_ctx = hashcat_ctx->combinator_ctx;

    if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_LEFT)
    {
      return strdup (combinator_ctx->dict2);
    }
    return strdup (combinator_ctx->dict1);
  }

  if (user_options->attack_mode == ATTACK_MODE_BF)
  {

  }

  if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    const mask_ctx_t *mask_ctx = hashcat_ctx->mask_ctx;

    return strdup (mask_ctx->mask);
  }

  if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
    {
      const straight_ctx_t *straight_ctx = hashcat_ctx->straight_ctx;

      return strdup (straight_ctx->dict);
    }

    const mask_ctx_t *mask_ctx = hashcat_ctx->mask_ctx;

    return strdup (mask_ctx->mask);
  }

  return NULL;
}