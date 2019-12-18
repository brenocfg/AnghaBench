#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_io {int dummy; } ;
struct bhnd_nvram_data {int /*<<< orphan*/  refs; TYPE_1__* cls; } ;
struct TYPE_3__ {int size; int (* op_new ) (struct bhnd_nvram_data*,struct bhnd_nvram_io*) ;} ;
typedef  TYPE_1__ bhnd_nvram_data_class ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 struct bhnd_nvram_data* bhnd_nv_calloc (int,int) ; 
 int /*<<< orphan*/  bhnd_nv_free (struct bhnd_nvram_data*) ; 
 int bhnd_nvram_data_probe_classes (struct bhnd_nvram_data**,struct bhnd_nvram_io*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int stub1 (struct bhnd_nvram_data*,struct bhnd_nvram_io*) ; 

int
bhnd_nvram_data_new(bhnd_nvram_data_class *cls, struct bhnd_nvram_data **nv,
    struct bhnd_nvram_io *io)
{
	struct bhnd_nvram_data	*data;
	int			 error;

	/* If NULL, try to identify the appropriate class */
	if (cls == NULL)
		return (bhnd_nvram_data_probe_classes(nv, io, NULL, 0));

	/* Allocate new instance */
	BHND_NV_ASSERT(sizeof(struct bhnd_nvram_data) <= cls->size,
	    ("instance size %zu less than minimum %zu", cls->size,
	     sizeof(struct bhnd_nvram_data)));

	data = bhnd_nv_calloc(1, cls->size);
	data->cls = cls;
	refcount_init(&data->refs, 1);

	/* Let the class handle initialization */
	if ((error = cls->op_new(data, io))) {
		bhnd_nv_free(data);
		return (error);
	}

	*nv = data;
	return (0);
}