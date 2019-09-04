#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int quiet; int keyspace; int stdout_flag; int show; int left; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  stop_buf ;
typedef  int /*<<< orphan*/  start_buf ;
struct TYPE_6__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctime_r (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  event_log_info_nn (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void goodbye_screen (hashcat_ctx_t *hashcat_ctx, const time_t proc_start, const time_t proc_stop)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->quiet       == true) return;
  if (user_options->keyspace    == true) return;
  if (user_options->stdout_flag == true) return;
  if (user_options->show        == true) return;
  if (user_options->left        == true) return;

  char start_buf[32]; memset (start_buf, 0, sizeof (start_buf));
  char stop_buf[32];  memset (start_buf, 0, sizeof (stop_buf));

  event_log_info_nn (hashcat_ctx, "Started: %s", ctime_r (&proc_start, start_buf));
  event_log_info_nn (hashcat_ctx, "Stopped: %s", ctime_r (&proc_stop,  stop_buf));
}