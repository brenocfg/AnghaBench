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
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  left; scalar_t__ buf; scalar_t__ ptr; } ;
typedef  TYPE_1__ dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  dl_zout_write_impl (TYPE_1__*,scalar_t__,scalar_t__) ; 

void dl_zout_flush (dl_zout *f) {
  ssize_t d = f->ptr - f->buf;
  if (d) {
    dl_zout_write_impl (f, f->buf, d);

    f->ptr = f->buf;
    f->left = f->buf_len;
  }
}