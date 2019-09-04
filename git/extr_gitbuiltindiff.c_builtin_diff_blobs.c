#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rev_info {int /*<<< orphan*/  diffopt; } ;
struct object_array_entry {unsigned int mode; TYPE_1__* item; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 unsigned int S_IFINVALID ; 
 int S_IFREG ; 
 int /*<<< orphan*/  blob_path (struct object_array_entry*) ; 
 int /*<<< orphan*/  builtin_diff_usage ; 
 unsigned int canon_mode (int) ; 
 int /*<<< orphan*/  diff_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diffcore_std (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stuff_change (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int builtin_diff_blobs(struct rev_info *revs,
			      int argc, const char **argv,
			      struct object_array_entry **blob)
{
	const unsigned mode = canon_mode(S_IFREG | 0644);

	if (argc > 1)
		usage(builtin_diff_usage);

	if (blob[0]->mode == S_IFINVALID)
		blob[0]->mode = mode;

	if (blob[1]->mode == S_IFINVALID)
		blob[1]->mode = mode;

	stuff_change(&revs->diffopt,
		     blob[0]->mode, blob[1]->mode,
		     &blob[0]->item->oid, &blob[1]->item->oid,
		     1, 1,
		     blob_path(blob[0]), blob_path(blob[1]));
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}