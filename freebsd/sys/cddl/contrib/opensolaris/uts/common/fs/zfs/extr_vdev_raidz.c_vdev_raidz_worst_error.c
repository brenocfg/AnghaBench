#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rm_cols; TYPE_1__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_4__ {int /*<<< orphan*/  rc_error; } ;

/* Variables and functions */
 int zio_worst_error (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_raidz_worst_error(raidz_map_t *rm)
{
	int error = 0;

	for (int c = 0; c < rm->rm_cols; c++)
		error = zio_worst_error(error, rm->rm_col[c].rc_error);

	return (error);
}