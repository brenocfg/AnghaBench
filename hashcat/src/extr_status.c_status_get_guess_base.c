#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ attack_mode; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_10__ {scalar_t__ wordlist_mode; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_11__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  mask; } ;
typedef  TYPE_4__ mask_ctx_t ;
struct TYPE_13__ {int opti_type; } ;
typedef  TYPE_5__ hashconfig_t ;
struct TYPE_14__ {TYPE_3__* straight_ctx; TYPE_4__* mask_ctx; TYPE_7__* combinator_ctx; TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_5__* hashconfig; } ;
typedef  TYPE_6__ hashcat_ctx_t ;
struct TYPE_15__ {scalar_t__ combs_mode; int /*<<< orphan*/  dict2; int /*<<< orphan*/  dict1; } ;
typedef  TYPE_7__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ COMBINATOR_MODE_BASE_LEFT ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 scalar_t__ WL_MODE_FILE ; 
 char* strdup (int /*<<< orphan*/ ) ; 

char *status_get_guess_base (const hashcat_ctx_t *hashcat_ctx)
{
  const hashconfig_t         *hashconfig         = hashcat_ctx->hashconfig;
  const user_options_t       *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    if (user_options_extra->wordlist_mode == WL_MODE_FILE)
    {
      const straight_ctx_t *straight_ctx = hashcat_ctx->straight_ctx;

      return strdup (straight_ctx->dict);
    }
  }

  if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    const combinator_ctx_t *combinator_ctx = hashcat_ctx->combinator_ctx;

    if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_LEFT)
    {
      return strdup (combinator_ctx->dict1);
    }
    return strdup (combinator_ctx->dict2);
  }

  if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    const mask_ctx_t *mask_ctx = hashcat_ctx->mask_ctx;

    return strdup (mask_ctx->mask);
  }

  if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    const straight_ctx_t *straight_ctx = hashcat_ctx->straight_ctx;

    return strdup (straight_ctx->dict);
  }

  if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
    {
      const mask_ctx_t *mask_ctx = hashcat_ctx->mask_ctx;

      return strdup (mask_ctx->mask);
    }

    const straight_ctx_t *straight_ctx = hashcat_ctx->straight_ctx;

    return strdup (straight_ctx->dict);
  }
  return NULL;
}