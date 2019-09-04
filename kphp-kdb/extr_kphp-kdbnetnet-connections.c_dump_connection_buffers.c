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
struct connection {int fd; int /*<<< orphan*/ * Tmp; int /*<<< orphan*/  Out; int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

void dump_connection_buffers (struct connection *c) {
  fprintf (stderr, "Dumping buffers of connection %d\nINPUT buffers of %d:\n", c->fd, c->fd);
  dump_buffers (&c->In);
  fprintf (stderr, "OUTPUT buffers of %d:\n", c->fd);
  dump_buffers (&c->Out);
  if (c->Tmp) {
    fprintf (stderr, "TEMP buffers of %d:\n", c->fd);
    dump_buffers (c->Tmp);
  }
  fprintf (stderr, "--- END (dumping buffers of connection %d) ---\n", c->fd);
}