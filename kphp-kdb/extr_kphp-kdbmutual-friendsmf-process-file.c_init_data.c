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
 int /*<<< orphan*/  input_name ; 
 int /*<<< orphan*/  open_file (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_name ; 

void init_data (void) {
  open_file (0, input_name, 0);
  open_file (1, output_name, 2);

/*  events_left = qmalloc (sizeof (short) * (userN + 2));
  int i;
  for (i = 0; i <= userN; i++) {
    events_left[i] = max_user_events;
  }*/
}