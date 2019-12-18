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
struct TYPE_7__ {int benchmark; int example_hashes; int keyspace; int left; int backend_info; int show; int stdout_flag; int speed_only; int progress_only; int usage; int version; } ;
typedef  TYPE_2__ user_options_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pfp; } ;
struct TYPE_8__ {int enabled; char* filename; TYPE_1__ fp; } ;
typedef  TYPE_3__ loopback_ctx_t ;
struct TYPE_9__ {TYPE_2__* user_options; TYPE_3__* loopback_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  HCBUFSIZ_TINY ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 

int loopback_init (hashcat_ctx_t *hashcat_ctx)
{
  loopback_ctx_t *loopback_ctx = hashcat_ctx->loopback_ctx;
  user_options_t *user_options = hashcat_ctx->user_options;

  loopback_ctx->enabled = false;

  if (user_options->benchmark      == true) return 0;
  if (user_options->example_hashes == true) return 0;
  if (user_options->keyspace       == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->backend_info   == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->stdout_flag    == true) return 0;
  if (user_options->speed_only     == true) return 0;
  if (user_options->progress_only  == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  loopback_ctx->enabled  = true;
  loopback_ctx->fp.pfp   = NULL;
  loopback_ctx->filename = (char *) hcmalloc (HCBUFSIZ_TINY);

  return 0;
}