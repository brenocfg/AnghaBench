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
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ sock_baton_t ;
typedef  int /*<<< orphan*/  apr_interval_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_socket_timeout_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sock_timeout_cb(void *baton, apr_interval_time_t interval)
{
  sock_baton_t *b = baton;
  apr_socket_timeout_set(b->sock, interval);
}