#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ generation; struct connection* conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  targ; } ;
struct TYPE_6__ {TYPE_2__ conn; TYPE_1__ targ; } ;
struct relative {int type; TYPE_3__ conn; } ;
struct connection {scalar_t__ generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct connection* get_target_connection (int /*<<< orphan*/ ) ; 

struct connection *get_relative_connection (struct relative *x) {
  if (!x) {
    return 0;
  }
  struct connection *c;
  if (x->type == 0) {
    c = get_target_connection (x->conn.targ.targ);
  } else if (x->type == 1) {
    c = x->conn.conn.conn;
    if (c && c->generation != x->conn.conn.generation) {
      c = 0;
    }
  } else {
    assert (0);
  }
  return c;
}