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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  In; scalar_t__ Tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_all_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_buffer (scalar_t__) ; 

void free_connection_buffers (struct connection *c) {
  if (c->Tmp) {
    free_buffer (c->Tmp);
    c->Tmp = 0;
  }
  free_all_buffers (&c->In);
  free_all_buffers (&c->Out);
}