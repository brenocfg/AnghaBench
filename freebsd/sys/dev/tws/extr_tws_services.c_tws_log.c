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
struct tws_softc {int /*<<< orphan*/  tws_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  severity_level; int /*<<< orphan*/  error_code; int /*<<< orphan*/  error_str; int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 TYPE_1__* array ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tws_log(struct tws_softc *sc, int index)
{
    device_printf((sc)->tws_dev, array[index].fmt,
                    array[index].error_str,
                    array[index].error_code,
                    array[index].severity_level,
                    array[index].desc );
}