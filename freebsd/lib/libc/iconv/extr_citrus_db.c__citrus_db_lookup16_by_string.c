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
typedef  int /*<<< orphan*/  uint16_t ;
struct _region {int dummy; } ;
struct _citrus_db_locator {int dummy; } ;
struct _citrus_db {int dummy; } ;

/* Variables and functions */
 int EFTYPE ; 
 int _citrus_db_lookup_by_string (struct _citrus_db*,char const*,struct _region*,struct _citrus_db_locator*) ; 
 int /*<<< orphan*/  _region_head (struct _region*) ; 
 int _region_size (struct _region*) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
_citrus_db_lookup16_by_string(struct _citrus_db *db, const char *key,
    uint16_t *rval, struct _citrus_db_locator *dl)
{
	struct _region r;
	int ret;
	uint16_t val;

	ret = _citrus_db_lookup_by_string(db, key, &r, dl);
	if (ret)
		return (ret);

	if (_region_size(&r) != 2)
		return (EFTYPE);

	if (rval) {
		memcpy(&val, _region_head(&r), 2);
		*rval = be16toh(val);
	}

	return (0);
}