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
struct TYPE_6__ {int logfile_disable; int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_7__ {char* subid; char* topid; int enabled; int /*<<< orphan*/  logfile; } ;
typedef  TYPE_2__ logfile_ctx_t ;
struct TYPE_8__ {TYPE_1__* user_options; TYPE_2__* logfile_ctx; TYPE_4__* folder_config; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  session_dir; } ;
typedef  TYPE_4__ folder_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  HCBUFSIZ_TINY ; 
 int /*<<< orphan*/  hc_asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 

int logfile_init (hashcat_ctx_t *hashcat_ctx)
{
  folder_config_t *folder_config = hashcat_ctx->folder_config;
  logfile_ctx_t   *logfile_ctx   = hashcat_ctx->logfile_ctx;
  user_options_t  *user_options  = hashcat_ctx->user_options;

  if (user_options->logfile_disable == true) return 0;

  hc_asprintf (&logfile_ctx->logfile, "%s/%s.log", folder_config->session_dir, user_options->session);

  logfile_ctx->subid = (char *) hcmalloc (HCBUFSIZ_TINY);
  logfile_ctx->topid = (char *) hcmalloc (HCBUFSIZ_TINY);

  logfile_ctx->enabled = true;

  return 0;
}