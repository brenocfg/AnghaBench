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
struct spi_device_id {size_t driver_data; } ;
struct altera_ps_data {size_t devtype; } ;
typedef  size_t kernel_ulong_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct altera_ps_data**) ; 
 struct altera_ps_data** altera_ps_data_map ; 

__attribute__((used)) static const struct altera_ps_data *id_to_data(const struct spi_device_id *id)
{
	kernel_ulong_t devtype = id->driver_data;
	const struct altera_ps_data *data;

	/* someone added a altera_ps_devtype without adding to the map array */
	if (devtype >= ARRAY_SIZE(altera_ps_data_map))
		return NULL;

	data = altera_ps_data_map[devtype];
	if (!data || data->devtype != devtype)
		return NULL;

	return data;
}