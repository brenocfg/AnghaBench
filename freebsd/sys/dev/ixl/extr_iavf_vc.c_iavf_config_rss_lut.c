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
typedef  int u32 ;
typedef  int u16 ;
struct virtchnl_rss_lut {int lut_entries; int* lut; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_4__ {int num_rx_queues; } ;
struct iavf_sc {TYPE_2__ vsi; TYPE_1__* vsi_res; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IXL_RSS_VSI_LUT_ENTRY_MASK ; 
 int IXL_RSS_VSI_LUT_SIZE ; 
 int /*<<< orphan*/  M_IAVF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_RSS_LUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct virtchnl_rss_lut*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct virtchnl_rss_lut* malloc (int,int /*<<< orphan*/ ,int) ; 
 int rss_get_indirection_to_bucket (int) ; 

int
iavf_config_rss_lut(struct iavf_sc *sc)
{
	struct virtchnl_rss_lut *rss_lut_msg;
	int msg_len;
	u16 lut_length;
	u32 lut;
	int i, que_id;

	lut_length = IXL_RSS_VSI_LUT_SIZE;
	msg_len = sizeof(struct virtchnl_rss_lut) + (lut_length * sizeof(u8)) - 1;
	rss_lut_msg = malloc(msg_len, M_IAVF, M_NOWAIT | M_ZERO);
	if (rss_lut_msg == NULL) {
		device_printf(sc->dev, "Unable to allocate msg memory for RSS lut msg.\n");
		return (ENOMEM);
	}

	rss_lut_msg->vsi_id = sc->vsi_res->vsi_id;
	/* Each LUT entry is a max of 1 byte, so this is easy */
	rss_lut_msg->lut_entries = lut_length;

	/* Populate the LUT with max no. of queues in round robin fashion */
	for (i = 0; i < lut_length; i++) {
#ifdef RSS
		/*
		 * Fetch the RSS bucket id for the given indirection entry.
		 * Cap it at the number of configured buckets (which is
		 * num_rx_queues.)
		 */
		que_id = rss_get_indirection_to_bucket(i);
		que_id = que_id % sc->vsi.num_rx_queues;
#else
		que_id = i % sc->vsi.num_rx_queues;
#endif
		lut = que_id & IXL_RSS_VSI_LUT_ENTRY_MASK;
		rss_lut_msg->lut[i] = lut;
	}

	iavf_send_pf_msg(sc, VIRTCHNL_OP_CONFIG_RSS_LUT,
			  (u8 *)rss_lut_msg, msg_len);

	free(rss_lut_msg, M_IAVF);
	return (0);
}