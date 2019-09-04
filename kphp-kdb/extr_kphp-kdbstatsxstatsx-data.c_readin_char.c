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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ rBuff ; 
 scalar_t__ rBuff_len ; 
 int rptr ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int readin_char () {
  rptr ++;
  if (rptr - rBuff > rBuff_len) {
    if (verbosity >= 1) {
      fprintf (stderr, "Buffer size %d seems to be too small. Skipping read.\n", rBuff_len);
    }
  }
  return *(char *)(rptr - 1);
}