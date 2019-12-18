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
struct pmac_i2c_host_kw {int /*<<< orphan*/  mutex; } ;
struct pmac_i2c_bus {struct pmac_i2c_host_kw* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kw_i2c_close(struct pmac_i2c_bus *bus)
{
	struct pmac_i2c_host_kw *host = bus->hostdata;
	mutex_unlock(&host->mutex);
}