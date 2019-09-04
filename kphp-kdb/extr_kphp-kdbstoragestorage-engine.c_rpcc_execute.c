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
struct connection {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int,int) ; 

int rpcc_execute (struct connection *c, int op, int len) {
  vkprintf (1, "rpcc_execute: fd=%d, op=%x, len=%d\n", c->fd, op, len);
  return SKIP_ALL_BYTES;
}