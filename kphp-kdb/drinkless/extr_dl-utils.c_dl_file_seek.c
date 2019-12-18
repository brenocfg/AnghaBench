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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int MAX_FN ; 
 int /*<<< orphan*/  assert (int) ; 
 int* fd ; 
 scalar_t__* fpos ; 
 scalar_t__ lseek (int,scalar_t__,int) ; 

off_t dl_file_seek (int x, off_t offset, int whence) {
  assert (0 <= x && x < MAX_FN);
  assert (fd[x] != -1);

  off_t res = lseek (fd[x], offset, whence);
  if (res != (off_t)-1) {
    fpos[x] = res;
  }
  return res;
}