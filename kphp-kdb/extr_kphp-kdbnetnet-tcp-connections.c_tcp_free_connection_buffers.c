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
struct connection {int /*<<< orphan*/  out_p; int /*<<< orphan*/  out; int /*<<< orphan*/  in_u; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  rwm_free (int /*<<< orphan*/ *) ; 

int tcp_free_connection_buffers (struct connection *c) {
  rwm_free (&c->in);
  rwm_free (&c->in_u);
  rwm_free (&c->out);
  rwm_free (&c->out_p);
  return 0;
}