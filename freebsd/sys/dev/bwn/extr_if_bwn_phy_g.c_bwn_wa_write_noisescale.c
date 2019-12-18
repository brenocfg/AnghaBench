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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_OFDMTAB_NOISESCALE ; 
 int BWN_TAB_NOISESCALE_SIZE ; 
 int /*<<< orphan*/  bwn_ofdmtab_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
bwn_wa_write_noisescale(struct bwn_mac *mac, const uint16_t *nst)
{
	int i;

	for (i = 0; i < BWN_TAB_NOISESCALE_SIZE; i++)
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_NOISESCALE, i, nst[i]);
}