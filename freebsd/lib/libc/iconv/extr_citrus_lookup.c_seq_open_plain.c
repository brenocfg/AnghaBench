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
struct _citrus_lookup {int cl_rewind; int /*<<< orphan*/ * cl_close; int /*<<< orphan*/ * cl_num_entries; int /*<<< orphan*/ * cl_lookup; int /*<<< orphan*/ * cl_next; int /*<<< orphan*/  cl_plainr; } ;

/* Variables and functions */
 int _map_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  seq_close_plain ; 
 int /*<<< orphan*/  seq_get_num_entries_plain ; 
 int /*<<< orphan*/  seq_lookup_plain ; 
 int /*<<< orphan*/  seq_next_plain ; 

__attribute__((used)) static int
seq_open_plain(struct _citrus_lookup *cl, const char *name)
{
	int ret;

	/* open read stream */
	ret = _map_file(&cl->cl_plainr, name);
	if (ret)
		return (ret);

	cl->cl_rewind = 1;
	cl->cl_next = &seq_next_plain;
	cl->cl_lookup = &seq_lookup_plain;
	cl->cl_num_entries = &seq_get_num_entries_plain;
	cl->cl_close = &seq_close_plain;

	return (0);
}