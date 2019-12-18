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
struct udf_node {int dummy; } ;
struct udf_mnt {int dummy; } ;
struct udf_dirstream {int offset; int fsize; struct udf_mnt* udfmp; struct udf_node* node; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  udf_zone_ds ; 
 struct udf_dirstream* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct udf_dirstream *
udf_opendir(struct udf_node *node, int offset, int fsize, struct udf_mnt *udfmp)
{
	struct udf_dirstream *ds;

	ds = uma_zalloc(udf_zone_ds, M_WAITOK | M_ZERO);

	ds->node = node;
	ds->offset = offset;
	ds->udfmp = udfmp;
	ds->fsize = fsize;

	return (ds);
}