#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int left; int ptr; } ;
typedef  TYPE_1__ dl_zin ;

/* Variables and functions */
 int /*<<< orphan*/  dl_zin_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,int,size_t) ; 

int dl_zin_read (dl_zin *f, void *dest, int len) {
  int tmp = len;
  while (len) {
    int cur = len;
    if (cur > f->left) {
      cur = f->left;
    }
    memcpy (dest, f->ptr, (size_t)cur);
    f->ptr += cur;
    f->left -= cur;

    if ((len -= cur) && !dl_zin_flush (f)) {
      return tmp - len;
    }
    dest += cur;
  }
  return tmp;
}