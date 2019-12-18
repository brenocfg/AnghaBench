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
struct udf_dirstream {int /*<<< orphan*/ * buf; scalar_t__ fid_fragment; int /*<<< orphan*/ * bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_UDFFID ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_zone_ds ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct udf_dirstream*) ; 

__attribute__((used)) static void
udf_closedir(struct udf_dirstream *ds)
{

	if (ds->bp != NULL)
		brelse(ds->bp);

	if (ds->fid_fragment && ds->buf != NULL)
		free(ds->buf, M_UDFFID);

	uma_zfree(udf_zone_ds, ds);
}