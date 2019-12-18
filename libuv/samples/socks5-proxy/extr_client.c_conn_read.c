#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;
struct TYPE_6__ {scalar_t__ rdstate; TYPE_1__ handle; } ;
typedef  TYPE_2__ conn ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ c_busy ; 
 scalar_t__ c_stop ; 
 int /*<<< orphan*/  conn_alloc ; 
 int /*<<< orphan*/  conn_read_done ; 
 int /*<<< orphan*/  conn_timer_reset (TYPE_2__*) ; 
 scalar_t__ uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conn_read(conn *c) {
  ASSERT(c->rdstate == c_stop);
  CHECK(0 == uv_read_start(&c->handle.stream, conn_alloc, conn_read_done));
  c->rdstate = c_busy;
  conn_timer_reset(c);
}