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
struct mps_softc {int dummy; } ;
struct mps_config_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int
mps_write_config_page(struct mps_softc *sc, struct mps_config_params *params)
{
	return (EINVAL);
}