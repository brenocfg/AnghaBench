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
struct serial {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INF_REG_EVENT ; 
 int /*<<< orphan*/  async_client_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_client_context ; 

__attribute__((used)) static void
remote_async_serial_handler (struct serial *scb, void *context)
{
  /* Don't propogate error information up to the client.  Instead let
     the client find out about the error by querying the target.  */
  async_client_callback (INF_REG_EVENT, async_client_context);
}