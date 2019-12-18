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
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct bwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_TXSTATUS0 ; 
 int BWI_TXSTATUS0_ACKED ; 
 int BWI_TXSTATUS0_AMPDU ; 
 int /*<<< orphan*/  BWI_TXSTATUS0_DATA_TXCNT_MASK ; 
 int BWI_TXSTATUS0_PENDING ; 
 int /*<<< orphan*/  BWI_TXSTATUS0_TXID_MASK ; 
 int BWI_TXSTATUS0_VALID ; 
 int /*<<< orphan*/  BWI_TXSTATUS1 ; 
 int CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 void* __SHIFTOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bwi_txeof (struct bwi_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwi_start_locked (struct bwi_softc*) ; 
 int /*<<< orphan*/  le16toh (void*) ; 

__attribute__((used)) static void
bwi_txeof(struct bwi_softc *sc)
{

	for (;;) {
		uint32_t tx_status0, tx_status1;
		uint16_t tx_id;
		int data_txcnt;

		tx_status0 = CSR_READ_4(sc, BWI_TXSTATUS0);
		if ((tx_status0 & BWI_TXSTATUS0_VALID) == 0)
			break;
		tx_status1 = CSR_READ_4(sc, BWI_TXSTATUS1);

		tx_id = __SHIFTOUT(tx_status0, BWI_TXSTATUS0_TXID_MASK);
		data_txcnt = __SHIFTOUT(tx_status0,
				BWI_TXSTATUS0_DATA_TXCNT_MASK);

		if (tx_status0 & (BWI_TXSTATUS0_AMPDU | BWI_TXSTATUS0_PENDING))
			continue;

		_bwi_txeof(sc, le16toh(tx_id), tx_status0 & BWI_TXSTATUS0_ACKED,
		    data_txcnt);
	}

	bwi_start_locked(sc);
}