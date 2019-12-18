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
struct TYPE_2__ {int processed; int offset; int invalid; int piping; int /*<<< orphan*/  resp_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 int getpid () ; 
 TYPE_1__* log_data ; 

__attribute__((used)) static void
dump_struct (FILE * fp)
{
  int pid = getpid ();
  if (!log_data)
    return;

  fprintf (fp, "==%d== VALUES AT CRASH POINT\n", pid);
  fprintf (fp, "==%d==\n", pid);
  fprintf (fp, "==%d== Line number: %u\n", pid, log_data->processed);
  fprintf (fp, "==%d== Offset: %u\n", pid, log_data->offset);
  fprintf (fp, "==%d== Invalid data: %u\n", pid, log_data->invalid);
  fprintf (fp, "==%d== Piping: %d\n", pid, log_data->piping);
  fprintf (fp, "==%d== Response size: %llu bytes\n", pid, log_data->resp_size);
  fprintf (fp, "==%d==\n", pid);
}