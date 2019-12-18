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
struct _citrus_lookup {scalar_t__ cl_dbidx; scalar_t__ cl_dbnum; int /*<<< orphan*/  cl_db; scalar_t__ cl_rewind; int /*<<< orphan*/  cl_dblocator; scalar_t__ cl_key; int /*<<< orphan*/  cl_keylen; } ;

/* Variables and functions */
 int ENOENT ; 
 int _db_get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _region*,struct _region*) ; 
 int _db_lookup_by_s (int /*<<< orphan*/ ,scalar_t__,struct _region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _region_init (struct _region*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
seq_next_db(struct _citrus_lookup *cl, struct _region *key,
    struct _region *data)
{

	if (cl->cl_key) {
		if (key)
			_region_init(key, cl->cl_key, cl->cl_keylen);
		return (_db_lookup_by_s(cl->cl_db, cl->cl_key, data,
		    &cl->cl_dblocator));
	}

	if (cl->cl_rewind) {
		cl->cl_dbidx = 0;
	}
	cl->cl_rewind = 0;
	if (cl->cl_dbidx >= cl->cl_dbnum)
		return (ENOENT);

	return (_db_get_entry(cl->cl_db, cl->cl_dbidx++, key, data));
}