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
struct connection {int unreliability; struct connection* next; } ;
struct conn_target {struct connection* first_conn; } ;

/* Variables and functions */
 scalar_t__ ROUND_ROBIN_EXTENSION ; 
 int cr_ok ; 
 int cr_stopped ; 
 int mcp_check_ready (struct connection*) ; 
 int /*<<< orphan*/  rotate_target (struct conn_target*,struct connection*) ; 

struct connection *get_target_connection (struct conn_target *S) {
  struct connection *c, *d = 0;
  int r, u = 10000;
  if (!S) {
    return 0;
  }
  for (c = S->first_conn; c != (struct connection *) S; c = c->next) {
    r = mcp_check_ready (c);
    if (r == cr_ok) {
      if (ROUND_ROBIN_EXTENSION) {
        rotate_target (S, c);
      }
      return c;
    } else if (r == cr_stopped && c->unreliability < u) {
      u = c->unreliability;
      d = c;
    }
  }
  /* all connections failed? */
  return d;
}