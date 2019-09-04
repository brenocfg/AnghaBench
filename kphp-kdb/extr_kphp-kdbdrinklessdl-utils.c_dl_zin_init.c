#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_3__ {int buf_len; int id; scalar_t__ r_left; scalar_t__ left; int /*<<< orphan*/  buf; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ dl_zin ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_malloc (size_t) ; 
 int /*<<< orphan*/ * fd ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void dl_zin_init (dl_zin *f, int id, int len) {
  f->buf_len = len;
  f->id = id;

  assert ("Too small buffer for input" && f->buf_len > 8);
  f->ptr = f->buf = dl_malloc ((size_t)f->buf_len);
  f->left = 0;

  off_t cur = lseek (fd[f->id], 0, SEEK_CUR),
        end = lseek (fd[f->id], 0, SEEK_END);
  lseek (fd[f->id], cur, SEEK_SET);
  f->r_left = end - cur;
}