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

/* Variables and functions */
 int /*<<< orphan*/  remote_async_ops ; 
 int /*<<< orphan*/  remote_mourn_1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remote_async_mourn (void)
{
  remote_mourn_1 (&remote_async_ops);
}