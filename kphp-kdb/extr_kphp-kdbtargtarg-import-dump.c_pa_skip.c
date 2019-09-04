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
 char* Pp ; 

__attribute__((used)) static inline int pa_skip (void) {
  if ((Pp[0] == '^' || !Pp[0]) && Pp[1] == '*' && Pp[2] == '^') {
    Pp += 3;
    return 1;
  } else {
    return 0;
  }
}