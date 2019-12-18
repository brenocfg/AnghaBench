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
struct ena_com_dev {int dummy; } ;
struct ena_adapter {struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ena_com_indirect_table_set (struct ena_com_dev*) ; 
 int ena_com_set_hash_ctrl (struct ena_com_dev*) ; 
 int ena_com_set_hash_function (struct ena_com_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_rss_configure(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	int rc;

	/* Set indirect table */
	rc = ena_com_indirect_table_set(ena_dev);
	if (unlikely((rc != 0) && (rc != EOPNOTSUPP)))
		return (rc);

	/* Configure hash function (if supported) */
	rc = ena_com_set_hash_function(ena_dev);
	if (unlikely((rc != 0) && (rc != EOPNOTSUPP)))
		return (rc);

	/* Configure hash inputs (if supported) */
	rc = ena_com_set_hash_ctrl(ena_dev);
	if (unlikely((rc != 0) && (rc != EOPNOTSUPP)))
		return (rc);

	return (0);
}