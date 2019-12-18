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
struct _citrus_db_locator {int dummy; } ;
struct _citrus_db {int dummy; } ;

/* Variables and functions */
 int EFTYPE ; 
 int _citrus_db_lookup_by_string (struct _citrus_db*,char const*,struct _region*,struct _citrus_db_locator*) ; 
 char* _region_head (struct _region*) ; 
 int _region_size (struct _region*) ; 

int
_citrus_db_lookup_string_by_string(struct _citrus_db *db, const char *key,
    const char **rdata, struct _citrus_db_locator *dl)
{
	struct _region r;
	int ret;

	ret = _citrus_db_lookup_by_string(db, key, &r, dl);
	if (ret)
		return (ret);

	/* check whether the string is null terminated */
	if (_region_size(&r) == 0)
		return (EFTYPE);
	if (*((const char*)_region_head(&r)+_region_size(&r)-1) != '\0')
		return (EFTYPE);

	if (rdata)
		*rdata = _region_head(&r);

	return (0);
}