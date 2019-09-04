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
 int /*<<< orphan*/  DEBUG_FILEDUMP ; 
 int /*<<< orphan*/  DEBUG_UDPDUMP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug_mode ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,int) ; 
 int /*<<< orphan*/  stderr ; 

int f_parse_option (int val) {
  switch (val) {
  case 'F':
    assert (!debug_mode);
    debug_mode = DEBUG_FILEDUMP;
    break;
  case 'U':
    assert (!debug_mode);
    debug_mode = DEBUG_UDPDUMP;
    break;
  default:
    fprintf (stderr, "Unimplemented option '%c' (%d)\n", (char) val, val);
    return -1;
  }
  return 0;
}