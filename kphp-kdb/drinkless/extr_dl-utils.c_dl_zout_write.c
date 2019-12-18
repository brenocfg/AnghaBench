#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int buf_len; int left; int ptr; } ;
typedef  TYPE_1__ dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  dl_zout_flush (TYPE_1__*) ; 
 int dl_zout_write_impl (TYPE_1__*,void const*,int) ; 
 int /*<<< orphan*/  memcpy (int,void const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

int dl_zout_write (dl_zout *f, const void *src, int len) {
  if (unlikely (len > f->buf_len)) {
    dl_zout_flush (f);
    return dl_zout_write_impl (f, src, len);
  }
  int save_len = len;
  while (len) {
    int cur = len;
    if (f->left < len) {
      cur = f->left;
    }
    memcpy (f->ptr, src, (size_t)cur);
    f->ptr += cur;
    f->left -= cur;

    if ((len -= cur)) {
      dl_zout_flush (f);
      src += cur;
    }
  }
  return save_len;
}