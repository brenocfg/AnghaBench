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
typedef  int /*<<< orphan*/  uint32_t ;
struct scard_data {scalar_t__ protocol; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  SCARD_PCI_T0 ; 
 int /*<<< orphan*/  SCARD_PCI_T1 ; 
 scalar_t__ SCARD_PROTOCOL_T1 ; 
 long SCARD_S_SUCCESS ; 
 long SCardTransmit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned long,int /*<<< orphan*/ *,unsigned char*,unsigned long*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,long) ; 

__attribute__((used)) static long scard_transmit(struct scard_data *scard,
			   unsigned char *_send, size_t send_len,
			   unsigned char *_recv, size_t *recv_len)
{
	long ret;
#ifdef __APPLE__
	uint32_t rlen;
#else
	unsigned long rlen;
#endif

	wpa_hexdump_key(MSG_DEBUG, "SCARD: scard_transmit: send",
			_send, send_len);
	rlen = *recv_len;
	ret = SCardTransmit(scard->card,
			    scard->protocol == SCARD_PROTOCOL_T1 ?
			    SCARD_PCI_T1 : SCARD_PCI_T0,
			    _send, (unsigned long) send_len,
			    NULL, _recv, &rlen);
	*recv_len = rlen;
	if (ret == SCARD_S_SUCCESS) {
		wpa_hexdump(MSG_DEBUG, "SCARD: scard_transmit: recv",
			    _recv, rlen);
	} else {
		wpa_printf(MSG_WARNING, "SCARD: SCardTransmit failed "
			   "(err=0x%lx)", ret);
	}
	return ret;
}