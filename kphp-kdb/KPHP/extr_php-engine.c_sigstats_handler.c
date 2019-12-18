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
struct TYPE_4__ {int sival_int; } ;
struct TYPE_5__ {scalar_t__ si_code; TYPE_1__ si_value; } ;
typedef  TYPE_2__ siginfo_t ;

/* Variables and functions */
 scalar_t__ SI_QUEUE ; 
 int SPOLL_SEND_FULL_STATS ; 
 int SPOLL_SEND_IMMEDIATE_STATS ; 
 int SPOLL_SEND_STATS ; 
 int /*<<< orphan*/  dl_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spoll_send_stats ; 
 int /*<<< orphan*/  write_immediate_stats_to_pipe () ; 

__attribute__((used)) static void sigstats_handler (int signum, siginfo_t *info, void *data) {
  dl_assert (info != NULL, "SIGPOLL with no info");
  if (info->si_code == SI_QUEUE) {
    int code = info->si_value.sival_int;
    if ((code & 0xFFFF0000)== SPOLL_SEND_STATS) {
      if (code & SPOLL_SEND_FULL_STATS) {
        spoll_send_stats++;
      }
      if (code & SPOLL_SEND_IMMEDIATE_STATS) {
        write_immediate_stats_to_pipe();
      }
    }
  }
}