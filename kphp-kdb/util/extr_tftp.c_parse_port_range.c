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
 int PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int max_port ; 
 int min_port ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int parse_port_range (char *s) {
  int x, y;
  if (sscanf (s, "%d-%d", &x, &y) != 2) {
    return -1;
  }
  if (x > y) {
    return -1;
  }
  if (x <= PRIVILEGED_TCP_PORTS) {
    fprintf (stderr, "min port number should be greater than PRIVILEGED_TCP_PORTS(%d)\n", PRIVILEGED_TCP_PORTS);
    return -1;
  }
  if (y >= 65536) {
    fprintf (stderr, "max port number should be less than 65536\n");
    return -1;
  }
  min_port = x;
  max_port = y;
  return 0;
}