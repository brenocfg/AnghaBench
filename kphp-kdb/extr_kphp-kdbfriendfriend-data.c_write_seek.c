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
 int /*<<< orphan*/  flushout () ; 
 long long lseek (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newidx_fd ; 
 long long write_pos ; 

__attribute__((used)) static void write_seek (long long new_pos) {
  flushout();
  assert (lseek (newidx_fd, new_pos, SEEK_SET) == new_pos);
  write_pos = new_pos;
}