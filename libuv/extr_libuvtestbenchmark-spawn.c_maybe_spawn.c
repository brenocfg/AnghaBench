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
 scalar_t__ N ; 
 scalar_t__ done ; 
 scalar_t__ pipe_open ; 
 scalar_t__ process_open ; 
 int /*<<< orphan*/  spawn () ; 

__attribute__((used)) static void maybe_spawn(void) {
  if (process_open == 0 && pipe_open == 0) {
    done++;
    if (done < N) {
      spawn();
    }
  }
}