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
struct connection {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_wait_answer ; 

__attribute__((used)) static int sqlc_connected (struct connection *c) {
  c->status = conn_wait_answer;
  return 0;
}