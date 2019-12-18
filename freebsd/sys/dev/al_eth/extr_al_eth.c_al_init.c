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
struct al_eth_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_init_locked (struct al_eth_adapter*) ; 

__attribute__((used)) static void
al_init(void *arg)
{
	struct al_eth_adapter *adapter = arg;

	al_init_locked(adapter);
}