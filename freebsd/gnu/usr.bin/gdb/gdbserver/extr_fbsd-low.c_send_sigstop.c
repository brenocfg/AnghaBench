#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; } ;
struct process_info {int sigstop_sent; TYPE_1__ head; scalar_t__ stop_expected; scalar_t__ stopped; } ;
struct inferior_list_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSTOP ; 
 scalar_t__ debug_threads ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
send_sigstop (struct inferior_list_entry *entry)
{
  struct process_info *process = (struct process_info *) entry;

  if (process->stopped)
    return;

  /* If we already have a pending stop signal for this process, don't
     send another.  */
  if (process->stop_expected)
    {
      process->stop_expected = 0;
      return;
    }

  if (debug_threads)
    fprintf (stderr, "Sending sigstop to process %d\n", process->head.id);

  kill (process->head.id, SIGSTOP);
  process->sigstop_sent = 1;
}