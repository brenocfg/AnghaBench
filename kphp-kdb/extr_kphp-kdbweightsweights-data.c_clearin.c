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
 int BUFFSIZE ; 
 int /*<<< orphan*/ * Buff ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int idx_crc32c_complement ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/ * rptr ; 
 int /*<<< orphan*/ * wptr ; 

__attribute__((used)) static void clearin (void) {
  if (Buff == NULL) {
    Buff = malloc (BUFFSIZE);
    assert (Buff);
  }
  rptr = wptr = Buff + BUFFSIZE;
  idx_crc32c_complement = -1;
}