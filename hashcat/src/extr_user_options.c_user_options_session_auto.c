#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* session; int benchmark; int example_hashes; int usage; int speed_only; int progress_only; int keyspace; int stdout_flag; int backend_info; int show; int left; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_5__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROGNAME ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void user_options_session_auto (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  if (strcmp (user_options->session, PROGNAME) == 0)
  {
    if (user_options->benchmark == true)
    {
      user_options->session = "benchmark";
    }

    if (user_options->example_hashes == true)
    {
      user_options->session = "example_hashes";
    }

    if (user_options->usage == true)
    {
      user_options->session = "usage";
    }

    if (user_options->speed_only == true)
    {
      user_options->session = "speed_only";
    }

    if (user_options->progress_only == true)
    {
      user_options->session = "progress_only";
    }

    if (user_options->keyspace == true)
    {
      user_options->session = "keyspace";
    }

    if (user_options->stdout_flag == true)
    {
      user_options->session = "stdout";
    }

    if (user_options->backend_info == true)
    {
      user_options->session = "backend_info";
    }

    if (user_options->show == true)
    {
      user_options->session = "show";
    }

    if (user_options->left == true)
    {
      user_options->session = "left";
    }
  }
}