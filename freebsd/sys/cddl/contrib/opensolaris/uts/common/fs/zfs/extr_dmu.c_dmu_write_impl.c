#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_6__ {int db_offset; int db_size; scalar_t__ db_data; } ;
typedef  TYPE_1__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ MIN (int,int) ; 
 int /*<<< orphan*/  bcopy (void const*,char*,int) ; 
 int /*<<< orphan*/  dmu_buf_fill_done (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_will_fill (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmu_write_impl(dmu_buf_t **dbp, int numbufs, uint64_t offset, uint64_t size,
    const void *buf, dmu_tx_t *tx)
{
	int i;

	for (i = 0; i < numbufs; i++) {
		int tocpy;
		int bufoff;
		dmu_buf_t *db = dbp[i];

		ASSERT(size > 0);

		bufoff = offset - db->db_offset;
		tocpy = (int)MIN(db->db_size - bufoff, size);

		ASSERT(i == 0 || i == numbufs-1 || tocpy == db->db_size);

		if (tocpy == db->db_size)
			dmu_buf_will_fill(db, tx);
		else
			dmu_buf_will_dirty(db, tx);

		bcopy(buf, (char *)db->db_data + bufoff, tocpy);

		if (tocpy == db->db_size)
			dmu_buf_fill_done(db, tx);

		offset += tocpy;
		size -= tocpy;
		buf = (char *)buf + tocpy;
	}
}