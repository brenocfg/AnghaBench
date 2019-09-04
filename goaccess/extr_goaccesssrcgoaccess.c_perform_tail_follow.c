#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  output_stdout; } ;
struct TYPE_3__ {scalar_t__ load_from_disk_only; int /*<<< orphan*/ * pipe; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__ conf ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ file_size (char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* glog ; 
 int /*<<< orphan*/  parse_tail_follow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tail_html () ; 
 int /*<<< orphan*/  tail_term () ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
perform_tail_follow (uint64_t * size1, const char *fn)
{
  FILE *fp = NULL;
  uint64_t size2 = 0;

  if (fn[0] == '-' && fn[1] == '\0') {
    parse_tail_follow (glog->pipe);
    goto out;
  }
  if (glog->load_from_disk_only)
    return;

  size2 = file_size (fn);

  /* file hasn't changed */
  if (size2 == *size1)
    return;

  if (!(fp = fopen (fn, "r")))
    FATAL ("Unable to read log file %s.", strerror (errno));

  if (!fseeko (fp, *size1, SEEK_SET))
    parse_tail_follow (fp);
  fclose (fp);

  *size1 = size2;

out:

  if (!conf.output_stdout)
    tail_term ();
  else
    tail_html ();

  usleep (200000);      /* 0.2 seconds */
}