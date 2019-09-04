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
struct TYPE_4__ {scalar_t__ ptr; scalar_t__ buf; int buf_len; int left; } ;
typedef  TYPE_1__ dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dl_malloc (size_t) ; 
 int /*<<< orphan*/  dl_zout_free_buffer (TYPE_1__*) ; 

void dl_zout_set_buffer_len (dl_zout *f, int len) {
  assert (f->ptr == f->buf);

  if (f->buf_len != len) {
    dl_zout_free_buffer (f);
    f->buf_len = len;
    assert ("Too small buffer for output" && f->buf_len > 8);
    f->buf = dl_malloc ((size_t)f->buf_len);
  }

  f->ptr = f->buf;
  f->left = f->buf_len;
}