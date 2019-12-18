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
typedef  size_t uint32_t ;
struct _memstream {int dummy; } ;
struct _citrus_region {int dummy; } ;
struct _citrus_db_locator {size_t dl_offset; size_t dl_hashval; } ;
struct _citrus_db_header_x {int /*<<< orphan*/  dex_data_size; int /*<<< orphan*/  dex_data_offset; int /*<<< orphan*/  dex_key_offset; int /*<<< orphan*/  dex_key_size; int /*<<< orphan*/  dex_hash_value; int /*<<< orphan*/  dex_next_offset; int /*<<< orphan*/  dhx_entry_offset; int /*<<< orphan*/  dhx_num_entries; } ;
struct _citrus_db_entry_x {int /*<<< orphan*/  dex_data_size; int /*<<< orphan*/  dex_data_offset; int /*<<< orphan*/  dex_key_offset; int /*<<< orphan*/  dex_key_size; int /*<<< orphan*/  dex_hash_value; int /*<<< orphan*/  dex_next_offset; int /*<<< orphan*/  dhx_entry_offset; int /*<<< orphan*/  dhx_num_entries; } ;
struct _citrus_db {size_t (* db_hashfunc ) (struct _citrus_region*) ;struct _citrus_region db_region; } ;

/* Variables and functions */
 int EFTYPE ; 
 int ENOENT ; 
 int /*<<< orphan*/  SEEK_SET ; 
 size_t _CITRUS_DB_ENTRY_SIZE ; 
 scalar_t__ _citrus_memory_stream_seek (struct _memstream*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _memstream_bind (struct _memstream*,struct _citrus_region*) ; 
 struct _citrus_db_header_x* _memstream_getregion (struct _memstream*,struct _citrus_region*,size_t) ; 
 scalar_t__ _memstream_seek (struct _memstream*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _region_head (struct _citrus_region*) ; 
 size_t _region_size (struct _citrus_region*) ; 
 size_t be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t stub1 (struct _citrus_region*) ; 

int
_citrus_db_lookup(struct _citrus_db *db, struct _citrus_region *key,
    struct _citrus_region *data, struct _citrus_db_locator *dl)
{
	struct _citrus_db_entry_x *dex;
	struct _citrus_db_header_x *dhx;
	struct _citrus_region r;
	struct _memstream ms;
	uint32_t hashval, num_entries;
	size_t offset;

	_memstream_bind(&ms, &db->db_region);

	dhx = _memstream_getregion(&ms, NULL, sizeof(*dhx));
	num_entries = be32toh(dhx->dhx_num_entries);
	if (num_entries == 0)
		return (ENOENT);

	if (dl != NULL && dl->dl_offset>0) {
		hashval = dl->dl_hashval;
		offset = dl->dl_offset;
		if (offset >= _region_size(&db->db_region))
			return (ENOENT);
	} else {
		hashval = db->db_hashfunc(key)%num_entries;
		offset = be32toh(dhx->dhx_entry_offset) +
		    hashval * _CITRUS_DB_ENTRY_SIZE;
		if (dl)
			dl->dl_hashval = hashval;
	}
	do {
		/* seek to the next entry */
		if (_citrus_memory_stream_seek(&ms, offset, SEEK_SET))
			return (EFTYPE);
		/* get the entry record */
		dex = _memstream_getregion(&ms, NULL, _CITRUS_DB_ENTRY_SIZE);
		if (dex == NULL)
			return (EFTYPE);

		/* jump to next entry having the same hash value. */
		offset = be32toh(dex->dex_next_offset);

		/* save the current position */
		if (dl) {
			dl->dl_offset = offset;
			if (offset == 0)
				dl->dl_offset = _region_size(&db->db_region);
		}

		/* compare hash value. */
		if (be32toh(dex->dex_hash_value) != hashval)
			/* not found */
			break;
		/* compare key length */
		if (be32toh(dex->dex_key_size) == _region_size(key)) {
			/* seek to the head of the key. */
			if (_memstream_seek(&ms, be32toh(dex->dex_key_offset),
			    SEEK_SET))
				return (EFTYPE);
			/* get the region of the key */
			if (_memstream_getregion(&ms, &r,
			    _region_size(key)) == NULL)
				return (EFTYPE);
			/* compare key byte stream */
			if (memcmp(_region_head(&r), _region_head(key),
			    _region_size(key)) == 0) {
				/* match */
				if (_memstream_seek(
				    &ms, be32toh(dex->dex_data_offset),
				    SEEK_SET))
					return (EFTYPE);
				if (_memstream_getregion(
				    &ms, data,
				    be32toh(dex->dex_data_size)) == NULL)
					return (EFTYPE);
				return (0);
			}
		}
	} while (offset != 0);

	return (ENOENT);
}