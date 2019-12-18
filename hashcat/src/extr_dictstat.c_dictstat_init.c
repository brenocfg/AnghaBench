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
struct TYPE_6__ {int benchmark; int example_hashes; int keyspace; int left; int backend_info; int show; int usage; int version; scalar_t__ attack_mode; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_7__ {TYPE_1__* user_options; TYPE_3__* folder_config; TYPE_4__* dictstat_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  profile_dir; } ;
typedef  TYPE_3__ folder_config_t ;
typedef  int /*<<< orphan*/  dictstat_t ;
struct TYPE_9__ {int enabled; int /*<<< orphan*/  filename; scalar_t__ cnt; int /*<<< orphan*/ * base; } ;
typedef  TYPE_4__ dictstat_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 int /*<<< orphan*/  DICTSTAT_FILENAME ; 
 int /*<<< orphan*/  MAX_DICTSTAT ; 
 int /*<<< orphan*/  hc_asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hccalloc (int /*<<< orphan*/ ,int) ; 

int dictstat_init (hashcat_ctx_t *hashcat_ctx)
{
  dictstat_ctx_t  *dictstat_ctx  = hashcat_ctx->dictstat_ctx;
  folder_config_t *folder_config = hashcat_ctx->folder_config;
  user_options_t  *user_options  = hashcat_ctx->user_options;

  dictstat_ctx->enabled = false;

  if (user_options->benchmark      == true) return 0;
  if (user_options->example_hashes == true) return 0;
  if (user_options->keyspace       == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->backend_info   == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  if (user_options->attack_mode == ATTACK_MODE_BF) return 0;

  dictstat_ctx->enabled  = true;
  dictstat_ctx->base     = (dictstat_t *) hccalloc (MAX_DICTSTAT, sizeof (dictstat_t));
  dictstat_ctx->cnt      = 0;

  hc_asprintf (&dictstat_ctx->filename, "%s/%s", folder_config->profile_dir, DICTSTAT_FILENAME);

  return 0;
}