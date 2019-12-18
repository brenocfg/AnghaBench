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
struct bhnd_nvram_store {int dummy; } ;
struct bhnd_nvram_io {int dummy; } ;
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_data_class ;

/* Variables and functions */
 int bhnd_nvram_data_new (int /*<<< orphan*/ *,struct bhnd_nvram_data**,struct bhnd_nvram_io*) ; 
 int /*<<< orphan*/  bhnd_nvram_data_release (struct bhnd_nvram_data*) ; 
 int bhnd_nvram_store_new (struct bhnd_nvram_store**,struct bhnd_nvram_data*) ; 

int
bhnd_nvram_store_parse_new(struct bhnd_nvram_store **store,
    struct bhnd_nvram_io *io, bhnd_nvram_data_class *cls)
{
	struct bhnd_nvram_data	*data;
	int			 error;


	/* Try to parse the data */
	if ((error = bhnd_nvram_data_new(cls, &data, io)))
		return (error);

	/* Try to create our new store instance */
	error = bhnd_nvram_store_new(store, data);
	bhnd_nvram_data_release(data);

	return (error);
}