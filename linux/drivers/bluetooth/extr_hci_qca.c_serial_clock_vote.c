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
struct qca_data {int tx_vote; int rx_vote; unsigned int vote_off_ms; unsigned int vote_on_ms; scalar_t__ vote_last_jif; int /*<<< orphan*/  votes_off; int /*<<< orphan*/  votes_on; int /*<<< orphan*/  rx_votes_off; int /*<<< orphan*/  tx_votes_off; int /*<<< orphan*/  rx_votes_on; int /*<<< orphan*/  tx_votes_on; } ;
struct hci_uart {int /*<<< orphan*/  tty; struct qca_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,char*,char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
#define  HCI_IBS_RX_VOTE_CLOCK_OFF 132 
#define  HCI_IBS_RX_VOTE_CLOCK_ON 131 
#define  HCI_IBS_TX_VOTE_CLOCK_OFF 130 
#define  HCI_IBS_TX_VOTE_CLOCK_ON 129 
#define  HCI_IBS_VOTE_STATS_UPDATE 128 
 int /*<<< orphan*/  __serial_clock_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __serial_clock_on (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 

__attribute__((used)) static void serial_clock_vote(unsigned long vote, struct hci_uart *hu)
{
	struct qca_data *qca = hu->priv;
	unsigned int diff;

	bool old_vote = (qca->tx_vote | qca->rx_vote);
	bool new_vote;

	switch (vote) {
	case HCI_IBS_VOTE_STATS_UPDATE:
		diff = jiffies_to_msecs(jiffies - qca->vote_last_jif);

		if (old_vote)
			qca->vote_off_ms += diff;
		else
			qca->vote_on_ms += diff;
		return;

	case HCI_IBS_TX_VOTE_CLOCK_ON:
		qca->tx_vote = true;
		qca->tx_votes_on++;
		new_vote = true;
		break;

	case HCI_IBS_RX_VOTE_CLOCK_ON:
		qca->rx_vote = true;
		qca->rx_votes_on++;
		new_vote = true;
		break;

	case HCI_IBS_TX_VOTE_CLOCK_OFF:
		qca->tx_vote = false;
		qca->tx_votes_off++;
		new_vote = qca->rx_vote | qca->tx_vote;
		break;

	case HCI_IBS_RX_VOTE_CLOCK_OFF:
		qca->rx_vote = false;
		qca->rx_votes_off++;
		new_vote = qca->rx_vote | qca->tx_vote;
		break;

	default:
		BT_ERR("Voting irregularity");
		return;
	}

	if (new_vote != old_vote) {
		if (new_vote)
			__serial_clock_on(hu->tty);
		else
			__serial_clock_off(hu->tty);

		BT_DBG("Vote serial clock %s(%s)", new_vote ? "true" : "false",
		       vote ? "true" : "false");

		diff = jiffies_to_msecs(jiffies - qca->vote_last_jif);

		if (new_vote) {
			qca->votes_on++;
			qca->vote_off_ms += diff;
		} else {
			qca->votes_off++;
			qca->vote_on_ms += diff;
		}
		qca->vote_last_jif = jiffies;
	}
}