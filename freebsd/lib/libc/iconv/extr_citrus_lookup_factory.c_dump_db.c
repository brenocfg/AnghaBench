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
struct _region {int dummy; } ;
struct _citrus_db_factory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CITRUS_LOOKUP_MAGIC ; 
 size_t _db_factory_calc_size (struct _citrus_db_factory*) ; 
 int _db_factory_serialize (struct _citrus_db_factory*,int /*<<< orphan*/ ,struct _region*) ; 
 int /*<<< orphan*/  _region_init (struct _region*,void*,size_t) ; 
 int errno ; 
 void* malloc (size_t) ; 

__attribute__((used)) static int
dump_db(struct _citrus_db_factory *df, struct _region *r)
{
	void *ptr;
	size_t size;

	size = _db_factory_calc_size(df);
	ptr = malloc(size);
	if (ptr == NULL)
		return (errno);
	_region_init(r, ptr, size);

	return (_db_factory_serialize(df, _CITRUS_LOOKUP_MAGIC, r));
}