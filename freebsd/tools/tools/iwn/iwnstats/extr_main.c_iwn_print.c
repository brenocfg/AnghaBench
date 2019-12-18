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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  general; int /*<<< orphan*/  ht; int /*<<< orphan*/  cck; int /*<<< orphan*/  ofdm; } ;
struct iwn_stats {int /*<<< orphan*/  tx; TYPE_1__ rx; } ;
struct iwnstats {struct iwn_stats st; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwn_stats_general_print (struct iwnstats*,struct iwn_stats*) ; 
 int /*<<< orphan*/  iwn_stats_ht_phy_print (struct iwnstats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwn_stats_phy_print (struct iwnstats*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iwn_stats_rx_general_print (struct iwnstats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwn_stats_tx_print (struct iwnstats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
iwn_print(struct iwnstats *is)
{
	struct iwn_stats *s;
	struct timeval tv;

	s = &is->st;

	gettimeofday(&tv, NULL);
	printf("time=%ld.%.6ld\n", (long)tv.tv_sec, (long)tv.tv_usec);

	iwn_stats_general_print(is, s);

	/* RX */
	iwn_stats_phy_print(is, &s->rx.ofdm, "ofdm");
	iwn_stats_phy_print(is, &s->rx.cck, "cck");
	iwn_stats_ht_phy_print(is, &s->rx.ht);
	iwn_stats_rx_general_print(is, &s->rx.general);

	/* TX */
	iwn_stats_tx_print(is, &s->tx);
	printf("--\n");
}