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

/* Variables and functions */
 char* cfg_cur ; 
 int cfg_lno ; 
 char* config_filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int syntax (const char *msg) {
  char *ptr = cfg_cur, *end = ptr + 20;
  if (!msg) {
    msg = "syntax error";
  }
  if (cfg_lno) {
    fprintf (stderr, "%s:%d: ", config_filename, cfg_lno);
  }
  fprintf (stderr, "fatal: %s near ", msg);
  while (*ptr && *ptr != 13 && *ptr != 10) {
    putc (*ptr++, stderr);
    if (ptr > end) {
      fprintf (stderr, " ...");
      break;
    }
  }
  putc ('\n', stderr);

  return -1;
}