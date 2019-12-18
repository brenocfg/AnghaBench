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
typedef  scalar_t__ uint32_t ;
struct _region {int dummy; } ;
struct _memstream {int dummy; } ;
struct _citrus_db_header_x {int /*<<< orphan*/  dex_data_size; int /*<<< orphan*/  dex_data_offset; int /*<<< orphan*/  dex_key_size; int /*<<< orphan*/  dex_key_offset; int /*<<< orphan*/  dhx_entry_offset; int /*<<< orphan*/  dhx_num_entries; } ;
struct _citrus_db_entry_x {int /*<<< orphan*/  dex_data_size; int /*<<< orphan*/  dex_data_offset; int /*<<< orphan*/  dex_key_size; int /*<<< orphan*/  dex_key_offset; int /*<<< orphan*/  dhx_entry_offset; int /*<<< orphan*/  dhx_num_entries; } ;
struct _citrus_db {int /*<<< orphan*/  db_region; } ;

/* Variables and functions */
 int EFTYPE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _CITRUS_DB_ENTRY_SIZE ; 
 scalar_t__ _citrus_memory_stream_seek (struct _memstream*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _memstream_bind (struct _memstream*,int /*<<< orphan*/ *) ; 
 struct _citrus_db_header_x* _memstream_getregion (struct _memstream*,struct _region*,int) ; 
 scalar_t__ _memstream_seek (struct _memstream*,int,int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 

int
_citrus_db_get_entry(struct _citrus_db *db, int idx, struct _region *key,
    struct _region *data)
{
	struct _citrus_db_entry_x *dex;
	struct _citrus_db_header_x *dhx;
	struct _memstream ms;
	uint32_t num_entries;
	size_t offset;

	_memstream_bind(&ms, &db->db_region);

	dhx = _memstream_getregion(&ms, NULL, sizeof(*dhx));
	num_entries = be32toh(dhx->dhx_num_entries);
	if (idx < 0 || (uint32_t)idx >= num_entries)
		return (EINVAL);

	/* seek to the next entry */
	offset = be32toh(dhx->dhx_entry_offset) + idx * _CITRUS_DB_ENTRY_SIZE;
	if (_citrus_memory_stream_seek(&ms, offset, SEEK_SET))
		return (EFTYPE);
	/* get the entry record */
	dex = _memstream_getregion(&ms, NULL, _CITRUS_DB_ENTRY_SIZE);
	if (dex == NULL)
		return (EFTYPE);
	/* seek to the head of the key. */
	if (_memstream_seek(&ms, be32toh(dex->dex_key_offset), SEEK_SET))
		return (EFTYPE);
	/* get the region of the key. */
	if (_memstream_getregion(&ms, key, be32toh(dex->dex_key_size))==NULL)
		return (EFTYPE);
	/* seek to the head of the data. */
	if (_memstream_seek(&ms, be32toh(dex->dex_data_offset), SEEK_SET))
		return (EFTYPE);
	/* get the region of the data. */
	if (_memstream_getregion(&ms, data, be32toh(dex->dex_data_size))==NULL)
		return (EFTYPE);

	return (0);
}