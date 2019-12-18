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
struct _citrus_db {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CITRUS_PIVOT_SUB_MAGIC ; 
 int /*<<< orphan*/  _db_hash_std ; 
 int _db_lookup_by_s (struct _citrus_db*,char const*,struct _region*,int /*<<< orphan*/ *) ; 
 int _db_open (struct _citrus_db**,struct _region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
open_subdb(struct _citrus_db **subdb, struct _citrus_db *db, const char *src)
{
	struct _region r;
	int ret;

	ret = _db_lookup_by_s(db, src, &r, NULL);
	if (ret)
		return (ret);
	ret = _db_open(subdb, &r, _CITRUS_PIVOT_SUB_MAGIC, _db_hash_std, NULL);
	if (ret)
		return (ret);

	return (0);
}