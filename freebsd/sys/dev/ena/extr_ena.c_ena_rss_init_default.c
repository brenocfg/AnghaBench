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
struct ena_adapter {int num_queues; int /*<<< orphan*/  pdev; struct ena_com_dev* ena_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_CRC32 ; 
 int /*<<< orphan*/  ENA_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  ENA_IO_RXQ_IDX (int) ; 
 int /*<<< orphan*/  ENA_RX_RSS_TABLE_LOG_SIZE ; 
 int ENA_RX_RSS_TABLE_SIZE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ena_com_fill_hash_function (struct ena_com_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ena_com_indirect_table_fill_entry (struct ena_com_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_rss_destroy (struct ena_com_dev*) ; 
 int ena_com_rss_init (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_com_set_default_hash_ctrl (struct ena_com_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ena_rss_init_default(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	device_t dev = adapter->pdev;
	int qid, rc, i;

	rc = ena_com_rss_init(ena_dev, ENA_RX_RSS_TABLE_LOG_SIZE);
	if (unlikely(rc != 0)) {
		device_printf(dev, "Cannot init indirect table\n");
		return (rc);
	}

	for (i = 0; i < ENA_RX_RSS_TABLE_SIZE; i++) {
		qid = i % adapter->num_queues;
		rc = ena_com_indirect_table_fill_entry(ena_dev, i,
		    ENA_IO_RXQ_IDX(qid));
		if (unlikely((rc != 0) && (rc != EOPNOTSUPP))) {
			device_printf(dev, "Cannot fill indirect table\n");
			goto err_rss_destroy;
		}
	}

	rc = ena_com_fill_hash_function(ena_dev, ENA_ADMIN_CRC32, NULL,
	    ENA_HASH_KEY_SIZE, 0xFFFFFFFF);
	if (unlikely((rc != 0) && (rc != EOPNOTSUPP))) {
		device_printf(dev, "Cannot fill hash function\n");
		goto err_rss_destroy;
	}

	rc = ena_com_set_default_hash_ctrl(ena_dev);
	if (unlikely((rc != 0) && (rc != EOPNOTSUPP))) {
		device_printf(dev, "Cannot fill hash control\n");
		goto err_rss_destroy;
	}

	return (0);

err_rss_destroy:
	ena_com_rss_destroy(ena_dev);
	return (rc);
}