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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct regmap_async_spi {TYPE_1__ m; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_async_complete_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regmap_spi_complete(void *data)
{
	struct regmap_async_spi *async = data;

	regmap_async_complete_cb(&async->core, async->m.status);
}