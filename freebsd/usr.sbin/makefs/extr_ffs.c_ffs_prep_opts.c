#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char member_0; char* member_1; int* member_2; int member_4; int member_5; char* member_6; int /*<<< orphan*/ * name; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ option_t ;
struct TYPE_8__ {int /*<<< orphan*/  fs_options; TYPE_3__* fs_specific; } ;
typedef  TYPE_2__ fsinfo_t ;
struct TYPE_9__ {int bsize; int fsize; int density; int minfree; int maxbpg; int avgfilesize; int avgfpdir; int maxbsize; int maxblkspercg; int version; int* label; int softupdates; int cpg; int optimization; int maxcontig; } ;
typedef  TYPE_3__ ffs_opt_t ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  OPT_INT32 ; 
 int /*<<< orphan*/  OPT_STRARRAY ; 
 int /*<<< orphan*/  OPT_STRBUF ; 
 int /*<<< orphan*/  copy_opts (TYPE_1__ const*) ; 
 TYPE_3__* ecalloc (int,int) ; 

void
ffs_prep_opts(fsinfo_t *fsopts)
{
	ffs_opt_t *ffs_opts = ecalloc(1, sizeof(*ffs_opts));

	const option_t ffs_options[] = {
	    { 'b', "bsize", &ffs_opts->bsize, OPT_INT32,
	      1, INT_MAX, "block size" },
	    { 'f', "fsize", &ffs_opts->fsize, OPT_INT32,
	      1, INT_MAX, "fragment size" },
	    { 'd', "density", &ffs_opts->density, OPT_INT32,
	      1, INT_MAX, "bytes per inode" },
	    { 'm', "minfree", &ffs_opts->minfree, OPT_INT32,
	      0, 99, "minfree" },
	    { 'M', "maxbpg", &ffs_opts->maxbpg, OPT_INT32,
	      1, INT_MAX, "max blocks per file in a cg" },
	    { 'a', "avgfilesize", &ffs_opts->avgfilesize, OPT_INT32,
	      1, INT_MAX, "expected average file size" },
	    { 'n', "avgfpdir", &ffs_opts->avgfpdir, OPT_INT32,
	      1, INT_MAX, "expected # of files per directory" },
	    { 'x', "extent", &ffs_opts->maxbsize, OPT_INT32,
	      1, INT_MAX, "maximum # extent size" },
	    { 'g', "maxbpcg", &ffs_opts->maxblkspercg, OPT_INT32,
	      1, INT_MAX, "max # of blocks per group" },
	    { 'v', "version", &ffs_opts->version, OPT_INT32,
	      1, 2, "UFS version" },
	    { 'o', "optimization", NULL, OPT_STRBUF,
	      0, 0, "Optimization (time|space)" },
	    { 'l', "label", ffs_opts->label, OPT_STRARRAY,
	      1, sizeof(ffs_opts->label), "UFS label" },
	    { 's', "softupdates", &ffs_opts->softupdates, OPT_INT32,
	      0, 1, "enable softupdates" },
	    { .name = NULL }
	};

	ffs_opts->bsize= -1;
	ffs_opts->fsize= -1;
	ffs_opts->cpg= -1;
	ffs_opts->density= -1;
	ffs_opts->minfree= -1;
	ffs_opts->optimization= -1;
	ffs_opts->maxcontig= -1;
	ffs_opts->maxbpg= -1;
	ffs_opts->avgfilesize= -1;
	ffs_opts->avgfpdir= -1;
	ffs_opts->version = 1;
	ffs_opts->softupdates = 0;

	fsopts->fs_specific = ffs_opts;
	fsopts->fs_options = copy_opts(ffs_options);
}