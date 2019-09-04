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
 int /*<<< orphan*/  BINLOG_NAME ; 
 int BINLOG_NAME_LEN ; 
 scalar_t__ BINLOG_POSITION ; 
 scalar_t__ EEXIST ; 
 scalar_t__ LAST_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int link (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int unlink (char*) ; 

void on_last_size (void) {
  if (BINLOG_POSITION > LAST_SIZE) {
    fprintf (stderr, "Expected size %lld, found %lld\n", LAST_SIZE, BINLOG_POSITION);
    return;
  }
  static char buf[1024];
  int s = BINLOG_NAME_LEN;
  memcpy (buf, BINLOG_NAME, s - 7);
  buf[s - 7] = 0;

  int r = link (BINLOG_NAME, buf);
  if (r < 0) {
    if (errno == EEXIST) {
      r = unlink (buf);
      if (r < 0) {
        fprintf (stderr, "Can not delete previous link: %m\n");
        assert (r == 0);
      }
      r = link (BINLOG_NAME, buf);
      if (r < 0) {
        fprintf (stderr, "Can not create link: %m\n");
        assert (r == 0);
      }
    } else {
      fprintf (stderr, "Can not create link: %m\n");
      assert (r == 0);
    }
  }
  assert (BINLOG_POSITION == LAST_SIZE);
}