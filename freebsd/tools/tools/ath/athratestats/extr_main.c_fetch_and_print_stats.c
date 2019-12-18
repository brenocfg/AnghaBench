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
typedef  int /*<<< orphan*/  uint8_t ;
struct ether_addr {int /*<<< orphan*/  octet; } ;
struct ath_ratestats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_BUF_SIZE ; 
 int /*<<< orphan*/  ath_rate_ioctl (struct ath_ratestats*) ; 
 int /*<<< orphan*/  ath_setsta (struct ath_ratestats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_node_stats (struct ath_ratestats*,struct ether_addr*) ; 

__attribute__((used)) static void
fetch_and_print_stats(struct ath_ratestats *r, struct ether_addr *e,
    uint8_t *buf)
{

	/* Zero the buffer before it's passed in */
	memset(buf, '\0', STATS_BUF_SIZE);

	/*
	 * Set the station address for this lookup.
	 */
	ath_setsta(r, e->octet);

	/*
	 * Fetch the data from the driver.
	 */
	ath_rate_ioctl(r);

	/*
	 * Decode and parse statistics.
	 */
	rate_node_stats(r, e);
}