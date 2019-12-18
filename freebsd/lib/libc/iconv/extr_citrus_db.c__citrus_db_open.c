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
struct _memstream {int dummy; } ;
struct _citrus_db_header_x {int /*<<< orphan*/  dhx_num_entries; int /*<<< orphan*/  dhx_entry_offset; int /*<<< orphan*/  dhx_magic; } ;
struct _citrus_db {void* db_hashfunc_closure; int /*<<< orphan*/  db_hashfunc; struct _region db_region; } ;
typedef  int /*<<< orphan*/  _citrus_db_hash_func_t ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _CITRUS_DB_ENTRY_SIZE ; 
 int /*<<< orphan*/  _CITRUS_DB_MAGIC_SIZE ; 
 int /*<<< orphan*/  _memstream_bind (struct _memstream*,struct _region*) ; 
 struct _citrus_db_header_x* _memstream_getregion (struct _memstream*,int /*<<< orphan*/ *,int) ; 
 int _memstream_remainder (struct _memstream*) ; 
 scalar_t__ _memstream_seek (struct _memstream*,int,int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int errno ; 
 struct _citrus_db* malloc (int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
_citrus_db_open(struct _citrus_db **rdb, struct _region *r, const char *magic,
    _citrus_db_hash_func_t hashfunc, void *hashfunc_closure)
{
	struct _citrus_db *db;
	struct _citrus_db_header_x *dhx;
	struct _memstream ms;

	_memstream_bind(&ms, r);

	/* sanity check */
	dhx = _memstream_getregion(&ms, NULL, sizeof(*dhx));
	if (dhx == NULL)
		return (EFTYPE);
	if (strncmp(dhx->dhx_magic, magic, _CITRUS_DB_MAGIC_SIZE) != 0)
		return (EFTYPE);
	if (_memstream_seek(&ms, be32toh(dhx->dhx_entry_offset), SEEK_SET))
		return (EFTYPE);

	if (be32toh(dhx->dhx_num_entries)*_CITRUS_DB_ENTRY_SIZE >
	    _memstream_remainder(&ms))
		return (EFTYPE);

	db = malloc(sizeof(*db));
	if (db == NULL)
		return (errno);
	db->db_region = *r;
	db->db_hashfunc = hashfunc;
	db->db_hashfunc_closure = hashfunc_closure;
	*rdb = db;

	return (0);
}