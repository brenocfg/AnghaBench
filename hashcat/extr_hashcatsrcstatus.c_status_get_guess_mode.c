#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rp_files_cnt; scalar_t__ rp_gen; scalar_t__ attack_mode; scalar_t__ custom_charset_4; scalar_t__ custom_charset_3; scalar_t__ custom_charset_2; scalar_t__ custom_charset_1; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_7__ {scalar_t__ wordlist_mode; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_8__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_4__* combinator_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_9__ {scalar_t__ combs_mode; } ;
typedef  TYPE_4__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 scalar_t__ COMBINATOR_MODE_BASE_LEFT ; 
 int GUESS_MODE_COMBINATOR_BASE_LEFT ; 
 int GUESS_MODE_COMBINATOR_BASE_RIGHT ; 
 int GUESS_MODE_HYBRID1 ; 
 int GUESS_MODE_HYBRID1_CS ; 
 int GUESS_MODE_HYBRID2 ; 
 int GUESS_MODE_HYBRID2_CS ; 
 int GUESS_MODE_MASK ; 
 int GUESS_MODE_MASK_CS ; 
 int GUESS_MODE_NONE ; 
 int GUESS_MODE_STRAIGHT_FILE ; 
 int GUESS_MODE_STRAIGHT_FILE_RULES_FILE ; 
 int GUESS_MODE_STRAIGHT_FILE_RULES_GEN ; 
 int GUESS_MODE_STRAIGHT_STDIN ; 
 int GUESS_MODE_STRAIGHT_STDIN_RULES_FILE ; 
 int GUESS_MODE_STRAIGHT_STDIN_RULES_GEN ; 
 scalar_t__ WL_MODE_FILE ; 

int status_get_guess_mode (const hashcat_ctx_t *hashcat_ctx)
{
  const combinator_ctx_t     *combinator_ctx     = hashcat_ctx->combinator_ctx;
  const user_options_t       *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  bool has_wordlist   = false;
  bool has_rule_file  = false;
  bool has_rule_gen   = false;
  bool has_base_left  = false;
  bool has_mask_cs    = false;

  if (user_options_extra->wordlist_mode == WL_MODE_FILE) has_wordlist = true;

  if (user_options->rp_files_cnt > 0) has_rule_file = true;
  if (user_options->rp_gen       > 0) has_rule_gen  = true;

  if (combinator_ctx->combs_mode == COMBINATOR_MODE_BASE_LEFT) has_base_left = true;

  if (user_options->custom_charset_1) has_mask_cs = true;
  if (user_options->custom_charset_2) has_mask_cs = true;
  if (user_options->custom_charset_3) has_mask_cs = true;
  if (user_options->custom_charset_4) has_mask_cs = true;

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    if (has_wordlist == true)
    {
      if (has_rule_file == true)
      {
        return GUESS_MODE_STRAIGHT_FILE_RULES_FILE;
      }
      else if (has_rule_gen == true)
      {
        return GUESS_MODE_STRAIGHT_FILE_RULES_GEN;
      }
      else
      {
        return GUESS_MODE_STRAIGHT_FILE;
      }
    }
    else
    {
      if (has_rule_file == true)
      {
        return GUESS_MODE_STRAIGHT_STDIN_RULES_FILE;
      }
      else if (has_rule_gen == true)
      {
        return GUESS_MODE_STRAIGHT_STDIN_RULES_GEN;
      }
      else
      {
        return GUESS_MODE_STRAIGHT_STDIN;
      }
    }
  }

  if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    if (has_base_left == true)
    {
      return GUESS_MODE_COMBINATOR_BASE_LEFT;
    }
    else
    {
      return GUESS_MODE_COMBINATOR_BASE_RIGHT;
    }
  }

  if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    if (has_mask_cs == true)
    {
      return GUESS_MODE_MASK_CS;
    }
    else
    {
      return GUESS_MODE_MASK;
    }
  }

  if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    if (has_mask_cs == true)
    {
      return GUESS_MODE_HYBRID1_CS;
    }
    else
    {
      return GUESS_MODE_HYBRID1;
    }
  }

  if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    if (has_mask_cs == true)
    {
      return GUESS_MODE_HYBRID2_CS;
    }
    else
    {
      return GUESS_MODE_HYBRID2;
    }
  }

  return GUESS_MODE_NONE;
}