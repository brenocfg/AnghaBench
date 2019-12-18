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
struct bhnd_nvram_io {int dummy; } ;
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_data_class ;

/* Variables and functions */
 int BHND_NVRAM_DATA_PROBE_MAYBE ; 
 int BHND_NVRAM_DATA_PROBE_SPECIFIC ; 
 int ENXIO ; 
 int /*<<< orphan*/ ** SET_BEGIN (int /*<<< orphan*/ ) ; 
 size_t SET_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_data_class_set ; 
 int bhnd_nvram_data_new (int /*<<< orphan*/ *,struct bhnd_nvram_data**,struct bhnd_nvram_io*) ; 
 int bhnd_nvram_data_probe (int /*<<< orphan*/ *,struct bhnd_nvram_io*) ; 
 int /*<<< orphan*/  bhnd_nvram_data_release (struct bhnd_nvram_data*) ; 

int
bhnd_nvram_data_probe_classes(struct bhnd_nvram_data **data,
    struct bhnd_nvram_io *io, bhnd_nvram_data_class *classes[],
    size_t num_classes)
{
	bhnd_nvram_data_class	*cls;
	int			 error, prio, result;

	cls = NULL;
	prio = 0;
	*data = NULL;

	/* If class array is NULL, default to our linker set */
	if (classes == NULL) {
		classes = SET_BEGIN(bhnd_nvram_data_class_set);
		num_classes = SET_COUNT(bhnd_nvram_data_class_set);
	}

	/* Try to find the best data class capable of parsing io */
	for (size_t i = 0; i < num_classes; i++) {
		bhnd_nvram_data_class *next_cls;

		next_cls = classes[i];

		/* Try to probe */
		result = bhnd_nvram_data_probe(next_cls, io);

		/* The parser did not match if an error was returned */
		if (result > 0)
			continue;

		/* Lower priority than previous match; keep
		 * searching */
		if (cls != NULL && result <= prio)
			continue;

		/* Drop any previously parsed data */
		if (*data != NULL) {
			bhnd_nvram_data_release(*data);
			*data = NULL;
		}

		/* If this is a 'maybe' match, attempt actual parsing to
		 * verify that this does in fact match */
		if (result <= BHND_NVRAM_DATA_PROBE_MAYBE) {
			/* If parsing fails, keep searching */
			error = bhnd_nvram_data_new(next_cls, data, io);
			if (error)
				continue;
		}

		/* Record best new match */
		prio = result;
		cls = next_cls;


		/* Terminate search immediately on
		 * BHND_NVRAM_DATA_PROBE_SPECIFIC */
		if (result == BHND_NVRAM_DATA_PROBE_SPECIFIC)
			break;
	}

	/* If no match, return error */
	if (cls == NULL)
		return (ENXIO);

	/* If the NVRAM data was not parsed above, do so now */
	if (*data == NULL) {
		if ((error = bhnd_nvram_data_new(cls, data, io)))
			return (error);
	}

	return (0);
}