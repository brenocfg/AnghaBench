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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void st_print_tspan (int sec) {
  if (sec < 60) {
    fprintf (stderr, "%d", sec);
  } else if (sec < 3600) {
    int minutes = sec / 60;
    fprintf (stderr, "%dm", minutes);
      fprintf (stderr, "%ds", sec % 60);
  } else if (sec < 86400) {
    int hours = sec / 3600;
    fprintf (stderr, "%dh", hours);
      fprintf (stderr, "%dm", (sec % 3600) / 60);
  } else if (sec < 31536000) {
    int days = sec / 86400;
    fprintf (stderr, "%dd", days);
      fprintf (stderr, "%dh", (sec % 86400) / 3600);
  } else {
    fprintf (stderr, ">year");
  }
}