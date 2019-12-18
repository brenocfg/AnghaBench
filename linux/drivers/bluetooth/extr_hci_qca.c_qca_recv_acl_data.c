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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ QCA_DEBUG_HANDLE ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int hci_recv_diag (struct hci_dev*,struct sk_buff*) ; 
 int hci_recv_frame (struct hci_dev*,struct sk_buff*) ; 

__attribute__((used)) static int qca_recv_acl_data(struct hci_dev *hdev, struct sk_buff *skb)
{
	/* We receive debug logs from chip as an ACL packets.
	 * Instead of sending the data to ACL to decode the
	 * received data, we are pushing them to the above layers
	 * as a diagnostic packet.
	 */
	if (get_unaligned_le16(skb->data) == QCA_DEBUG_HANDLE)
		return hci_recv_diag(hdev, skb);

	return hci_recv_frame(hdev, skb);
}