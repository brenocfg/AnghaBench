#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  In; int /*<<< orphan*/ * Tmp; TYPE_1__* gather; } ;
struct TYPE_2__ {struct connection* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_all_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_gather (TYPE_1__*) ; 

void free_connection_buffers (struct connection *c) {
  if (c->gather && c->gather->c == c) {
    free_gather (c->gather);
  }
  c->gather = 0;
  if (c->Tmp) {
    free_all_buffers (c->Tmp);
    c->Tmp = 0;
  }
  free_all_buffers (&c->In);
  free_all_buffers (&c->Out);
}