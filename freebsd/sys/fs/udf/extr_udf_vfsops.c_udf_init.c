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
typedef  int /*<<< orphan*/  unicode_t ;
struct vfsconf {int dummy; } ;
struct udf_node {int dummy; } ;
struct udf_dirstream {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAXNAMLEN ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * udf_zone_ds ; 
 int /*<<< orphan*/ * udf_zone_node ; 
 int /*<<< orphan*/ * udf_zone_trans ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udf_init(struct vfsconf *foo)
{

	/*
	 * This code used to pre-allocate a certain number of pages for each
	 * pool, reducing the need to grow the zones later on.  UMA doesn't
	 * advertise any such functionality, unfortunately =-<
	 */
	udf_zone_trans = uma_zcreate("UDF translation buffer, zone", MAXNAMLEN *
	    sizeof(unicode_t), NULL, NULL, NULL, NULL, 0, 0);

	udf_zone_node = uma_zcreate("UDF Node zone", sizeof(struct udf_node),
	    NULL, NULL, NULL, NULL, 0, 0);

	udf_zone_ds = uma_zcreate("UDF Dirstream zone",
	    sizeof(struct udf_dirstream), NULL, NULL, NULL, NULL, 0, 0);

	if ((udf_zone_node == NULL) || (udf_zone_trans == NULL) ||
	    (udf_zone_ds == NULL)) {
		printf("Cannot create allocation zones.\n");
		return (ENOMEM);
	}

	return 0;
}