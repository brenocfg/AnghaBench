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
typedef  int /*<<< orphan*/  client_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE () ; 
 int do_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_handshake_auth(client_ctx *cx) {
  UNREACHABLE();
  return do_kill(cx);
}