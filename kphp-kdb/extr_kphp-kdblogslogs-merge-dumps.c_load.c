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
 scalar_t__ BUFF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* f_buff ; 
 scalar_t__* f_buff_r ; 
 scalar_t__* f_buff_size ; 
 int /*<<< orphan*/ * fd ; 
 int* fsize ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int read (int /*<<< orphan*/ ,scalar_t__,int) ; 

int load (int en) {
  if (fsize[en] <= 0) {
    assert (fsize[en] == 0);
    return -1;
  }
  if (f_buff_r[en] < f_buff_size[en]) {
//    fprintf (stderr, "%d %d\n", f_buff_r[en], f_buff_size[en]);
    assert (f_buff_r[en] > f_buff_size[en] - f_buff_r[en]);
    memcpy (f_buff[en], f_buff[en] + f_buff_r[en], f_buff_size[en] - f_buff_r[en]);
  }
  f_buff_size[en] -= f_buff_r[en];
  f_buff_r[en] = 0;
  assert (0 <= f_buff_size[en]);

  int need = BUFF_SIZE - f_buff_size[en];
  if (fsize[en] < need) {
    need = fsize[en];
  }

//  fprintf (stderr, "Loading from %d dump %d bytes, already readed %llu, %lld bytes to read\n", en, need, lseek (fd[en], 0, SEEK_CUR), fsize[en]);
  assert (read (fd[en], f_buff[en] + f_buff_size[en], need) == need);
  f_buff_size[en] += need;
  fsize[en] -= need;

  return 1;
}