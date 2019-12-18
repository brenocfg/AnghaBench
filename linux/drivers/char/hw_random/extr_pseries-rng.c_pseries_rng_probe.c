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
struct vio_device_id {int dummy; } ;
struct vio_dev {int dummy; } ;

/* Variables and functions */
 int hwrng_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseries_rng ; 

__attribute__((used)) static int pseries_rng_probe(struct vio_dev *dev,
		const struct vio_device_id *id)
{
	return hwrng_register(&pseries_rng);
}