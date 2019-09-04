#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int filenames_idx; char** filenames; int /*<<< orphan*/  read_stdin; scalar_t__ load_from_disk; } ;
struct TYPE_6__ {int load_from_disk_only; } ;
typedef  TYPE_1__ GLog ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char const*) ; 
 TYPE_5__ conf ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ pre_process_log (TYPE_1__*,char*,int) ; 
 scalar_t__ read_log (TYPE_1__**,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* verify_formats () ; 

int
parse_log (GLog ** glog, char *tail, int dry_run)
{
  const char *err_log = NULL;
  int i;

  /* process tail data and return */
  if (tail != NULL) {
    /* no line testing on tail */
    if (pre_process_log ((*glog), tail, dry_run))
      return 1;
    return 0;
  }

  /* verify that we have the required formats */
  if ((err_log = verify_formats ()))
    FATAL ("%s", err_log);

  /* no data piped, no logs passed, load from disk only then */
  if (conf.load_from_disk && !conf.filenames_idx && !conf.read_stdin) {
    (*glog)->load_from_disk_only = 1;
    return 0;
  }

  for (i = 0; i < conf.filenames_idx; ++i) {
    if (read_log (glog, conf.filenames[i], dry_run)) {
      fprintf (stderr, "%s\n", conf.filenames[i]);
      return 1;
    }
  }

  return 0;
}