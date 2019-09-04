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
 scalar_t__ SIGTERM_MAX_TIMEOUT ; 
 scalar_t__ precise_now ; 
 int sigterm_on ; 
 scalar_t__ sigterm_time ; 

__attribute__((used)) static void turn_sigterm_on (void) {
  if (sigterm_on != 1) {
    sigterm_time = precise_now + SIGTERM_MAX_TIMEOUT;
    sigterm_on = 1;
  }
}