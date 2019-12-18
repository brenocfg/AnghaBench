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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,int) ; 
 int index_mode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  udp_enabled ; 

int f_parse_option (int val) {
  switch (val) {
  case 'U':
    udp_enabled++;
    break;
  case 'i':
    index_mode = 1;
    break;
  default:
    fprintf (stderr, "Unimplemented option '%c' (%d)\n", (char) val, val);
    return -1;
  }
  return 0;
}