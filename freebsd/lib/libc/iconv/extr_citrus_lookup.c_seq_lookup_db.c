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
struct _citrus_lookup {int /*<<< orphan*/  cl_dblocator; int /*<<< orphan*/  cl_key; int /*<<< orphan*/  cl_db; int /*<<< orphan*/  cl_keylen; scalar_t__ cl_ignore_case; scalar_t__ cl_rewind; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bcs_convert_to_lower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _db_locator_init (int /*<<< orphan*/ *) ; 
 int _db_lookup_by_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
seq_lookup_db(struct _citrus_lookup *cl, const char *key, struct _region *data)
{

	cl->cl_rewind = 0;
	free(cl->cl_key);
	cl->cl_key = strdup(key);
	if (cl->cl_ignore_case)
		_bcs_convert_to_lower(cl->cl_key);
	cl->cl_keylen = strlen(cl->cl_key);
	_db_locator_init(&cl->cl_dblocator);
	return (_db_lookup_by_s(cl->cl_db, cl->cl_key, data,
	    &cl->cl_dblocator));
}