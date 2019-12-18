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
typedef  int /*<<< orphan*/  u16 ;
struct ena_com_dev {int /*<<< orphan*/  rss; } ;

/* Variables and functions */
 int ena_com_hash_ctrl_init (struct ena_com_dev*) ; 
 int ena_com_hash_key_allocate (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_hash_key_destroy (struct ena_com_dev*) ; 
 int ena_com_indirect_table_allocate (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_indirect_table_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_rss_init(struct ena_com_dev *ena_dev, u16 indr_tbl_log_size)
{
	int rc;

	memset(&ena_dev->rss, 0x0, sizeof(ena_dev->rss));

	rc = ena_com_indirect_table_allocate(ena_dev, indr_tbl_log_size);
	if (unlikely(rc))
		goto err_indr_tbl;

	rc = ena_com_hash_key_allocate(ena_dev);
	if (unlikely(rc))
		goto err_hash_key;

	rc = ena_com_hash_ctrl_init(ena_dev);
	if (unlikely(rc))
		goto err_hash_ctrl;

	return 0;

err_hash_ctrl:
	ena_com_hash_key_destroy(ena_dev);
err_hash_key:
	ena_com_indirect_table_destroy(ena_dev);
err_indr_tbl:

	return rc;
}