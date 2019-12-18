#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int quiet; int keyspace; int stdout_flag; int show; int left; int benchmark; int machine_readable; int workload_profile_chgd; int restore; int speed_only; int progress_only; int force; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_8__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROGNAME ; 
 int /*<<< orphan*/  event_log_advice (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  event_log_info (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_2__*,char*) ; 

void welcome_screen (hashcat_ctx_t *hashcat_ctx, const char *version_tag)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->quiet       == true) return;
  if (user_options->keyspace    == true) return;
  if (user_options->stdout_flag == true) return;
  if (user_options->show        == true) return;
  if (user_options->left        == true) return;

  if (user_options->benchmark == true)
  {
    if (user_options->machine_readable == false)
    {
      event_log_info (hashcat_ctx, "%s (%s) starting in benchmark mode...", PROGNAME, version_tag);

      event_log_info (hashcat_ctx, NULL);

      if (user_options->workload_profile_chgd == false)
      {
        event_log_advice (hashcat_ctx, "Benchmarking uses hand-optimized kernel code by default.");
        event_log_advice (hashcat_ctx, "You can use it in your cracking session by setting the -O option.");
        event_log_advice (hashcat_ctx, "Note: Using optimized kernel code limits the maximum supported password length.");
        event_log_advice (hashcat_ctx, "To disable the optimized kernel code in benchmark mode, use the -w option.");
        event_log_advice (hashcat_ctx, NULL);
      }
    }
    else
    {
      event_log_info (hashcat_ctx, "# version: %s", version_tag);
    }
  }
  else if (user_options->restore == true)
  {
    event_log_info (hashcat_ctx, "%s (%s) starting in restore mode...", PROGNAME, version_tag);
    event_log_info (hashcat_ctx, NULL);
  }
  else if (user_options->speed_only == true)
  {
    event_log_info (hashcat_ctx, "%s (%s) starting in speed-only mode...", PROGNAME, version_tag);
    event_log_info (hashcat_ctx, NULL);
  }
  else if (user_options->progress_only == true)
  {
    event_log_info (hashcat_ctx, "%s (%s) starting in progress-only mode...", PROGNAME, version_tag);
    event_log_info (hashcat_ctx, NULL);
  }
  else
  {
    event_log_info (hashcat_ctx, "%s (%s) starting...", PROGNAME, version_tag);
    event_log_info (hashcat_ctx, NULL);
  }

  if (user_options->force == true)
  {
    event_log_warning (hashcat_ctx, "You have enabled --force to bypass dangerous warnings and errors!");
    event_log_warning (hashcat_ctx, "This can hide serious problems and should only be done when debugging.");
    event_log_warning (hashcat_ctx, "Do not report hashcat issues encountered when using --force.");
  }
}