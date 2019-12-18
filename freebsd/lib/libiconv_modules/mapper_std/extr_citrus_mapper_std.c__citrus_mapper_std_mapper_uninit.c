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
struct _citrus_mapper_std {int /*<<< orphan*/  ms_file; int /*<<< orphan*/  ms_db; int /*<<< orphan*/  (* ms_uninit ) (struct _citrus_mapper_std*) ;} ;
struct _citrus_mapper {struct _citrus_mapper_std* cm_closure; } ;

/* Variables and functions */
 int /*<<< orphan*/  _db_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _unmap_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct _citrus_mapper_std*) ; 
 int /*<<< orphan*/  stub1 (struct _citrus_mapper_std*) ; 

__attribute__((used)) static void
/*ARGSUSED*/
_citrus_mapper_std_mapper_uninit(struct _citrus_mapper *cm)
{
	struct _citrus_mapper_std *ms;

	ms = cm->cm_closure;
	if (ms->ms_uninit)
		(*ms->ms_uninit)(ms);
	_db_close(ms->ms_db);
	_unmap_file(&ms->ms_file);
	free(ms);
}