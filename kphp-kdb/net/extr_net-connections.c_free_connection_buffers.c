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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_all_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 

int free_connection_buffers (struct connection *c) {
  free_tmp_buffers (c);
  free_all_buffers (&c->In);
  free_all_buffers (&c->Out);
  return 0;
}