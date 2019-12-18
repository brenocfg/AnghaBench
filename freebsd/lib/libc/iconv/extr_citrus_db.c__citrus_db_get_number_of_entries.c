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
struct _memstream {int dummy; } ;
struct _citrus_db_header_x {int /*<<< orphan*/  dhx_num_entries; } ;
struct _citrus_db {int /*<<< orphan*/  db_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  _memstream_bind (struct _memstream*,int /*<<< orphan*/ *) ; 
 struct _citrus_db_header_x* _memstream_getregion (struct _memstream*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 

int
_citrus_db_get_number_of_entries(struct _citrus_db *db)
{
	struct _citrus_db_header_x *dhx;
	struct _memstream ms;

	_memstream_bind(&ms, &db->db_region);

	dhx = _memstream_getregion(&ms, NULL, sizeof(*dhx));
	return ((int)be32toh(dhx->dhx_num_entries));
}