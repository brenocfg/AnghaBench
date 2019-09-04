#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lev_generic {int type; int b; } ;

/* Variables and functions */
#define  LEV_START 129 
#define  LEV_TAG 128 
 char act ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_tag ; 
 int /*<<< orphan*/  convert_md5_to_hex (char*,int /*<<< orphan*/ ) ; 
 int default_replay_logevent (struct lev_generic*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int start ; 

int tag_replay_logevent (struct lev_generic *E, int size) {
  int s;
  switch (E->type) {
    case LEV_START:
      assert (!start && !log_cur_pos ());
      if (size < 24 || E->b < 0 || E->b > 4096) { return -2; }
      s = 24 + ((E->b + 3) & -4);
      if (size < s) { return -2; }
      start = 1;
      return s;
    case LEV_TAG:
      s = default_replay_logevent (E, size);
      if (act == 'i') {
        char output[33];
        convert_md5_to_hex (output, binlog_tag);
        printf ("%s\n", output);
        exit (0);
      }
      kprintf ("ERROR: binlog has already a tag.\n");
      return -1;
  }
  kprintf ("unexpected log event type %08x at position %lld\n", E->type, log_cur_pos ());
  return -1;
}