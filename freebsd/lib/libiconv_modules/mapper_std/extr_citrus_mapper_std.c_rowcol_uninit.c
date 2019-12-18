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
struct _citrus_mapper_std_rowcol {int /*<<< orphan*/  rc_src_rowcol; } ;
struct _citrus_mapper_std {struct _citrus_mapper_std_rowcol ms_rowcol; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rowcol_uninit(struct _citrus_mapper_std *ms)
{
	struct _citrus_mapper_std_rowcol *rc;

	rc = &ms->ms_rowcol;
	free(rc->rc_src_rowcol);
}