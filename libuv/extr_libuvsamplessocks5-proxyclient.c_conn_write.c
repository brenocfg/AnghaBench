#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* base; unsigned int len; } ;
typedef  TYPE_2__ uv_buf_t ;
struct TYPE_7__ {int /*<<< orphan*/  stream; } ;
struct TYPE_9__ {scalar_t__ wrstate; TYPE_1__ handle; int /*<<< orphan*/  write_req; } ;
typedef  TYPE_3__ conn ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ c_busy ; 
 scalar_t__ c_done ; 
 scalar_t__ c_stop ; 
 int /*<<< orphan*/  conn_timer_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  conn_write_done ; 
 scalar_t__ uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conn_write(conn *c, const void *data, unsigned int len) {
  uv_buf_t buf;

  ASSERT(c->wrstate == c_stop || c->wrstate == c_done);
  c->wrstate = c_busy;

  /* It's okay to cast away constness here, uv_write() won't modify the
   * memory.
   */
  buf.base = (char *) data;
  buf.len = len;

  CHECK(0 == uv_write(&c->write_req,
                      &c->handle.stream,
                      &buf,
                      1,
                      conn_write_done));
  conn_timer_reset(c);
}