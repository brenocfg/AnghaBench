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
struct intel_data {int /*<<< orphan*/  flags; struct hci_uart* hu; int /*<<< orphan*/  busy_work; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct intel_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_BOOTING ; 
 int /*<<< orphan*/  hci_uart_has_flow_control (struct hci_uart*) ; 
 int /*<<< orphan*/  intel_busy_work ; 
 int /*<<< orphan*/  intel_set_power (struct hci_uart*,int) ; 
 struct intel_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_open(struct hci_uart *hu)
{
	struct intel_data *intel;

	BT_DBG("hu %p", hu);

	if (!hci_uart_has_flow_control(hu))
		return -EOPNOTSUPP;

	intel = kzalloc(sizeof(*intel), GFP_KERNEL);
	if (!intel)
		return -ENOMEM;

	skb_queue_head_init(&intel->txq);
	INIT_WORK(&intel->busy_work, intel_busy_work);

	intel->hu = hu;

	hu->priv = intel;

	if (!intel_set_power(hu, true))
		set_bit(STATE_BOOTING, &intel->flags);

	return 0;
}