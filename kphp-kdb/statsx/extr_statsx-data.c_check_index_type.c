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
 scalar_t__ get_index_version (int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,int*,int) ; 

int check_index_type (int idx_fd) {
  lseek (idx_fd, 0, SEEK_SET);
  int magic;
  read (idx_fd, &magic, sizeof (int));
  if (get_index_version (magic) < 0) {
    return -1;
  }
  lseek (idx_fd, 0, SEEK_SET);
  return 0;
}