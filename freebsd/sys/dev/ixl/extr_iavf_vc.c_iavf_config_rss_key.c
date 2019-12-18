#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct virtchnl_rss_key {int key_len; int /*<<< orphan*/  vsi_id; int /*<<< orphan*/ * key; } ;
struct iavf_sc {TYPE_1__* vsi_res; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IXL_RSS_KEY_SIZE ; 
 int /*<<< orphan*/  M_IAVF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_RSS_KEY ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct virtchnl_rss_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_dbg_vc (struct iavf_sc*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ixl_get_default_rss_key (int /*<<< orphan*/ *) ; 
 struct virtchnl_rss_key* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rss_getkey (int /*<<< orphan*/ *) ; 

int
iavf_config_rss_key(struct iavf_sc *sc)
{
	struct virtchnl_rss_key *rss_key_msg;
	int msg_len, key_length;
	u8		rss_seed[IXL_RSS_KEY_SIZE];

#ifdef RSS
	/* Fetch the configured RSS key */
	rss_getkey((uint8_t *) &rss_seed);
#else
	ixl_get_default_rss_key((u32 *)rss_seed);
#endif

	/* Send the fetched key */
	key_length = IXL_RSS_KEY_SIZE;
	msg_len = sizeof(struct virtchnl_rss_key) + (sizeof(u8) * key_length) - 1;
	rss_key_msg = malloc(msg_len, M_IAVF, M_NOWAIT | M_ZERO);
	if (rss_key_msg == NULL) {
		device_printf(sc->dev, "Unable to allocate msg memory for RSS key msg.\n");
		return (ENOMEM);
	}

	rss_key_msg->vsi_id = sc->vsi_res->vsi_id;
	rss_key_msg->key_len = key_length;
	bcopy(rss_seed, &rss_key_msg->key[0], key_length);

	iavf_dbg_vc(sc, "config_rss: vsi_id %d, key_len %d\n",
	    rss_key_msg->vsi_id, rss_key_msg->key_len);
	
	iavf_send_pf_msg(sc, VIRTCHNL_OP_CONFIG_RSS_KEY,
			  (u8 *)rss_key_msg, msg_len);

	free(rss_key_msg, M_IAVF);
	return (0);
}