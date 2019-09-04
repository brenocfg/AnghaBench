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
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  update_precise_now () ; 

__attribute__((used)) inline static int get_ms_timeout (double timeout) {
  if (timeout == 0) {
    return 0;
  }
  if (timeout < 0 || timeout >= 1e100) {
    return -1;
  }
  update_precise_now ();
  timeout -= precise_now;
  if (timeout < 0) {
    return 0;
  } else {
    return (int)(timeout * 1000);
  }
}