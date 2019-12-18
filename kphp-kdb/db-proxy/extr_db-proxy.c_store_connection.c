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
struct connection {int /*<<< orphan*/  unreliability; int /*<<< orphan*/  ready; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/ * R_end ; 

void store_connection (struct connection *c) {
  R_end[0] = c->fd;
  R_end[1] = c->status;
  R_end[2] = c->flags;
  R_end[3] = c->ready;
  R_end[4] = c->unreliability;
  R_end += 5;
}