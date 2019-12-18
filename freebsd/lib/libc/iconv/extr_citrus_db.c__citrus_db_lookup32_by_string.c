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
typedef  int /*<<< orphan*/  uint32_t ;
struct _region {int dummy; } ;
struct _citrus_db_locator {int dummy; } ;
struct _citrus_db {int dummy; } ;

/* Variables and functions */
 int EFTYPE ; 
 int _citrus_db_lookup_by_string (struct _citrus_db*,char const*,struct _region*,struct _citrus_db_locator*) ; 
 int /*<<< orphan*/  _region_head (struct _region*) ; 
 int _region_size (struct _region*) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
_citrus_db_lookup32_by_string(struct _citrus_db *db, const char *key,
    uint32_t *rval, struct _citrus_db_locator *dl)
{
	struct _region r;
	uint32_t val;
	int ret;

	ret = _citrus_db_lookup_by_string(db, key, &r, dl);
	if (ret)
		return (ret);

	if (_region_size(&r) != 4)
		return (EFTYPE);

	if (rval) {
		memcpy(&val, _region_head(&r), 4);
		*rval = be32toh(val);
	}

	return (0);
}