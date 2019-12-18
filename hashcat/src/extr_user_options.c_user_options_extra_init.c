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
struct TYPE_5__ {int attack_mode; int benchmark; int example_hashes; int backend_info; int keyspace; int hc_argc; int stdout_flag; int /*<<< orphan*/ ** hc_argv; int /*<<< orphan*/  rule_buf_r; int /*<<< orphan*/  rule_buf_l; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_6__ {scalar_t__ attack_kern; int rule_len_l; int rule_len_r; int hc_workc; void* wordlist_mode; int /*<<< orphan*/ ** hc_workv; int /*<<< orphan*/ * hc_hash; } ;
typedef  TYPE_2__ user_options_extra_t ;
struct TYPE_7__ {TYPE_2__* user_options_extra; TYPE_1__* user_options; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_BF ; 
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_NONE ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 
#define  ATTACK_MODE_BF 132 
#define  ATTACK_MODE_COMBI 131 
#define  ATTACK_MODE_HYBRID1 130 
#define  ATTACK_MODE_HYBRID2 129 
#define  ATTACK_MODE_STRAIGHT 128 
 void* WL_MODE_FILE ; 
 void* WL_MODE_MASK ; 
 void* WL_MODE_NONE ; 
 void* WL_MODE_STDIN ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void user_options_extra_init (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t       *user_options       = hashcat_ctx->user_options;
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  // attack-kern

  user_options_extra->attack_kern = ATTACK_KERN_NONE;

  switch (user_options->attack_mode)
  {
    case ATTACK_MODE_STRAIGHT: user_options_extra->attack_kern = ATTACK_KERN_STRAIGHT; break;
    case ATTACK_MODE_COMBI:    user_options_extra->attack_kern = ATTACK_KERN_COMBI;    break;
    case ATTACK_MODE_BF:       user_options_extra->attack_kern = ATTACK_KERN_BF;       break;
    case ATTACK_MODE_HYBRID1:  user_options_extra->attack_kern = ATTACK_KERN_COMBI;    break;
    case ATTACK_MODE_HYBRID2:  user_options_extra->attack_kern = ATTACK_KERN_COMBI;    break;
  }

  // rules

  user_options_extra->rule_len_l = (int) strlen (user_options->rule_buf_l);
  user_options_extra->rule_len_r = (int) strlen (user_options->rule_buf_r);

  // hc_hash and hc_work*

  user_options_extra->hc_hash  = NULL;
  user_options_extra->hc_workv = NULL;
  user_options_extra->hc_workc = 0;

  if (user_options->benchmark == true)
  {

  }
  else if (user_options->example_hashes == true)
  {

  }
  else if (user_options->backend_info == true)
  {

  }
  else if (user_options->keyspace == true)
  {
    user_options_extra->hc_workc = user_options->hc_argc;
    user_options_extra->hc_workv = user_options->hc_argv;
  }
  else if (user_options->stdout_flag == true)
  {
    user_options_extra->hc_workc = user_options->hc_argc;
    user_options_extra->hc_workv = user_options->hc_argv;
  }
  else
  {
    user_options_extra->hc_hash  = user_options->hc_argv[0];
    user_options_extra->hc_workc = user_options->hc_argc - 1;
    user_options_extra->hc_workv = user_options->hc_argv + 1;
  }

  // wordlist_mode

  user_options_extra->wordlist_mode = WL_MODE_NONE;

  if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
  {
    user_options_extra->wordlist_mode = (user_options_extra->hc_workc >= 1) ? WL_MODE_FILE : WL_MODE_STDIN;
  }
  else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
  {
    user_options_extra->wordlist_mode = WL_MODE_FILE;
  }
  else if (user_options_extra->attack_kern == ATTACK_KERN_BF)
  {
    user_options_extra->wordlist_mode = WL_MODE_MASK;
  }
}