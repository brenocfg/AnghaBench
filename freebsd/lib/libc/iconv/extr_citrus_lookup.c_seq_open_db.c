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
struct _citrus_lookup {int cl_rewind; int /*<<< orphan*/ * cl_close; int /*<<< orphan*/ * cl_num_entries; int /*<<< orphan*/ * cl_next; int /*<<< orphan*/ * cl_lookup; scalar_t__ cl_dbidx; int /*<<< orphan*/  cl_db; int /*<<< orphan*/  cl_dbnum; struct _region cl_dbfile; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  _CITRUS_LOOKUP_MAGIC ; 
 int /*<<< orphan*/  _db_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _db_hash_std ; 
 int _db_open (int /*<<< orphan*/ *,struct _region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _map_file (struct _region*,char*) ; 
 int /*<<< orphan*/  _unmap_file (struct _region*) ; 
 int /*<<< orphan*/  seq_close_db ; 
 int /*<<< orphan*/  seq_get_num_entries_db ; 
 int /*<<< orphan*/  seq_lookup_db ; 
 int /*<<< orphan*/  seq_next_db ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
seq_open_db(struct _citrus_lookup *cl, const char *name)
{
	struct _region r;
	char path[PATH_MAX];
	int ret;

	snprintf(path, sizeof(path), "%s.db", name);
	ret = _map_file(&r, path);
	if (ret)
		return (ret);

	ret = _db_open(&cl->cl_db, &r, _CITRUS_LOOKUP_MAGIC,
	    _db_hash_std, NULL);
	if (ret) {
		_unmap_file(&r);
		return (ret);
	}

	cl->cl_dbfile = r;
	cl->cl_dbnum = _db_get_num_entries(cl->cl_db);
	cl->cl_dbidx = 0;
	cl->cl_rewind = 1;
	cl->cl_lookup = &seq_lookup_db;
	cl->cl_next = &seq_next_db;
	cl->cl_num_entries = &seq_get_num_entries_db;
	cl->cl_close = &seq_close_db;

	return (0);
}