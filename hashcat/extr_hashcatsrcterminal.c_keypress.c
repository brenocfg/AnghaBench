#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int quiet; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_14__ {scalar_t__ devices_status; int shutdown_outer; int checkpoint_shutdown; int /*<<< orphan*/  mux_display; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_15__ {TYPE_1__* user_options; TYPE_2__* status_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ResumeThreads (TYPE_3__*) ; 
 scalar_t__ STATUS_INIT ; 
 scalar_t__ STATUS_PAUSED ; 
 int /*<<< orphan*/  SuspendThreads (TYPE_3__*) ; 
 int /*<<< orphan*/  bypass (TYPE_3__*) ; 
 int /*<<< orphan*/  event_log_info (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  hc_thread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_thread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myquit (TYPE_3__*) ; 
 int /*<<< orphan*/  send_prompt (TYPE_3__*) ; 
 int /*<<< orphan*/  status_display (TYPE_3__*) ; 
 int /*<<< orphan*/  stop_at_checkpoint (TYPE_3__*) ; 
 int /*<<< orphan*/  tty_break () ; 
 int /*<<< orphan*/  tty_fix () ; 
 int tty_getchar () ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void keypress (hashcat_ctx_t *hashcat_ctx)
{
  status_ctx_t   *status_ctx   = hashcat_ctx->status_ctx;
  user_options_t *user_options = hashcat_ctx->user_options;

  // this is required, because some of the variables down there are not initialized at that point
  while (status_ctx->devices_status == STATUS_INIT) usleep (100000);

  const bool quiet = user_options->quiet;

  tty_break ();

  while (status_ctx->shutdown_outer == false)
  {
    int ch = tty_getchar ();

    if (ch == -1) break;

    if (ch ==  0) continue;

    //https://github.com/hashcat/hashcat/issues/302
    //#if defined (_POSIX)
    //if (ch != '\n')
    //#endif

    hc_thread_mutex_lock (status_ctx->mux_display);

    event_log_info (hashcat_ctx, NULL);

    switch (ch)
    {
      case 's':
      case '\r':
      case '\n':

        event_log_info (hashcat_ctx, NULL);

        status_display (hashcat_ctx);

        event_log_info (hashcat_ctx, NULL);

        if (quiet == false) send_prompt (hashcat_ctx);

        break;

      case 'b':

        event_log_info (hashcat_ctx, NULL);

        bypass (hashcat_ctx);

        event_log_info (hashcat_ctx, "Next dictionary / mask in queue selected. Bypassing current one.");

        event_log_info (hashcat_ctx, NULL);

        if (quiet == false) send_prompt (hashcat_ctx);

        break;

      case 'p':

        if (status_ctx->devices_status != STATUS_PAUSED)
        {
          event_log_info (hashcat_ctx, NULL);

          SuspendThreads (hashcat_ctx);

          if (status_ctx->devices_status == STATUS_PAUSED)
          {
            event_log_info (hashcat_ctx, "Paused");
          }

          event_log_info (hashcat_ctx, NULL);
        }

        if (quiet == false) send_prompt (hashcat_ctx);

        break;

      case 'r':

        if (status_ctx->devices_status == STATUS_PAUSED)
        {
          event_log_info (hashcat_ctx, NULL);

          ResumeThreads (hashcat_ctx);

          if (status_ctx->devices_status != STATUS_PAUSED)
          {
            event_log_info (hashcat_ctx, "Resumed");
          }

          event_log_info (hashcat_ctx, NULL);
        }

        if (quiet == false) send_prompt (hashcat_ctx);

        break;

      case 'c':

        event_log_info (hashcat_ctx, NULL);

        stop_at_checkpoint (hashcat_ctx);

        if (status_ctx->checkpoint_shutdown == true)
        {
          event_log_info (hashcat_ctx, "Checkpoint enabled. Will quit at next restore-point update.");
        }
        else
        {
          event_log_info (hashcat_ctx, "Checkpoint disabled. Restore-point updates will no longer be monitored.");
        }

        event_log_info (hashcat_ctx, NULL);

        if (quiet == false) send_prompt (hashcat_ctx);

        break;

      case 'q':

        event_log_info (hashcat_ctx, NULL);

        myquit (hashcat_ctx);

        break;

      default:

        if (quiet == false) send_prompt (hashcat_ctx);

        break;
    }

    //https://github.com/hashcat/hashcat/issues/302
    //#if defined (_POSIX)
    //if (ch != '\n')
    //#endif

    hc_thread_mutex_unlock (status_ctx->mux_display);
  }

  tty_fix ();
}