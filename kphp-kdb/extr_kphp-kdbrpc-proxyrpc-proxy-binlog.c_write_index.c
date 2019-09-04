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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cur ; 
 int /*<<< orphan*/  ifd ; 
 int /*<<< orphan*/  last ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void write_index (void) {
  if (memcmp (last, cur, 20)) {
    lseek (ifd, 0, SEEK_SET);
    assert (write (ifd, cur, 20) == 20);
    memcpy (last, cur, 20);
  }
}