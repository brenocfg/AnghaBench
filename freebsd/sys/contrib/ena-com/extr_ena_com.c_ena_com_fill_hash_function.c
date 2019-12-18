#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct ena_rss {int hash_func; void* hash_init_val; int /*<<< orphan*/  hash_key_dma_addr; struct ena_admin_feature_rss_flow_hash_control* hash_key; } ;
struct ena_com_dev {struct ena_rss rss; } ;
struct TYPE_3__ {int supported_func; } ;
struct TYPE_4__ {TYPE_1__ flow_hash_func; } ;
struct ena_admin_get_feat_resp {TYPE_2__ u; } ;
struct ena_admin_feature_rss_flow_hash_control {int keys_num; int /*<<< orphan*/  key; } ;
typedef  enum ena_admin_hash_functions { ____Placeholder_ena_admin_hash_functions } ena_admin_hash_functions ;

/* Variables and functions */
#define  ENA_ADMIN_CRC32 129 
 int /*<<< orphan*/  ENA_ADMIN_RSS_HASH_FUNCTION ; 
#define  ENA_ADMIN_TOEPLITZ 128 
 int ENA_COM_INVAL ; 
 int ENA_COM_UNSUPPORTED ; 
 int ena_com_get_feature_ex (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_get_hash_function (struct ena_com_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ena_com_set_hash_function (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_trc_err (char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_fill_hash_function(struct ena_com_dev *ena_dev,
			       enum ena_admin_hash_functions func,
			       const u8 *key, u16 key_len, u32 init_val)
{
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_get_feat_resp get_resp;
	struct ena_admin_feature_rss_flow_hash_control *hash_key =
		rss->hash_key;
	int rc;

	/* Make sure size is a mult of DWs */
	if (unlikely(key_len & 0x3))
		return ENA_COM_INVAL;

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_HASH_FUNCTION,
				    rss->hash_key_dma_addr,
				    sizeof(*rss->hash_key), 0);
	if (unlikely(rc))
		return rc;

	if (!((1 << func) & get_resp.u.flow_hash_func.supported_func)) {
		ena_trc_err("Flow hash function %d isn't supported\n", func);
		return ENA_COM_UNSUPPORTED;
	}

	switch (func) {
	case ENA_ADMIN_TOEPLITZ:
		if (key_len > sizeof(hash_key->key)) {
			ena_trc_err("key len (%hu) is bigger than the max supported (%zu)\n",
				    key_len, sizeof(hash_key->key));
			return ENA_COM_INVAL;
		}

		memcpy(hash_key->key, key, key_len);
		rss->hash_init_val = init_val;
		hash_key->keys_num = key_len >> 2;
		break;
	case ENA_ADMIN_CRC32:
		rss->hash_init_val = init_val;
		break;
	default:
		ena_trc_err("Invalid hash function (%d)\n", func);
		return ENA_COM_INVAL;
	}

	rss->hash_func = func;
	rc = ena_com_set_hash_function(ena_dev);

	/* Restore the old function */
	if (unlikely(rc))
		ena_com_get_hash_function(ena_dev, NULL, NULL);

	return rc;
}