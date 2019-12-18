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
struct solos_card {TYPE_1__* dev; } ;
struct sk_buff {int len; } ;
struct pkt_hdr {void* type; void* vci; void* vpi; void* size; } ;
struct atm_vcc {int vpi; int vci; TYPE_2__* dev; } ;
struct TYPE_4__ {struct solos_card* dev_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PKT_DATA ; 
 int /*<<< orphan*/  SOLOS_CHAN (TYPE_2__*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fpga_queue (struct solos_card*,int /*<<< orphan*/ ,struct sk_buff*,struct atm_vcc*) ; 
 int pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clone_writable (struct sk_buff*,int) ; 
 int skb_headroom (struct sk_buff*) ; 
 struct pkt_hdr* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  solos_pop (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static int psend(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct solos_card *card = vcc->dev->dev_data;
	struct pkt_hdr *header;
	int pktlen;

	pktlen = skb->len;
	if (pktlen > (BUF_SIZE - sizeof(*header))) {
		dev_warn(&card->dev->dev, "Length of PDU is too large. Dropping PDU.\n");
		solos_pop(vcc, skb);
		return 0;
	}

	if (!skb_clone_writable(skb, sizeof(*header))) {
		int expand_by = 0;
		int ret;

		if (skb_headroom(skb) < sizeof(*header))
			expand_by = sizeof(*header) - skb_headroom(skb);

		ret = pskb_expand_head(skb, expand_by, 0, GFP_ATOMIC);
		if (ret) {
			dev_warn(&card->dev->dev, "pskb_expand_head failed.\n");
			solos_pop(vcc, skb);
			return ret;
		}
	}

	header = skb_push(skb, sizeof(*header));

	/* This does _not_ include the size of the header */
	header->size = cpu_to_le16(pktlen);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_DATA);

	fpga_queue(card, SOLOS_CHAN(vcc->dev), skb, vcc);

	return 0;
}