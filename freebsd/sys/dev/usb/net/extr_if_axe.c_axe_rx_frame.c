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
struct usb_page_cache {int dummy; } ;
struct usb_ether {int /*<<< orphan*/  ue_ifp; } ;
struct axe_softc {int sc_flags; int sc_lenmask; } ;
struct axe_sframe_hdr {int len; int ilen; int cstatus; } ;
struct axe_csum_hdr {int len; int ilen; int cstatus; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  csum_hdr ;

/* Variables and functions */
 int AXE_CSUM_RXBYTES (int) ; 
 int AXE_FLAG_CSUM_FRAME ; 
 int AXE_FLAG_STD_FRAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  axe_rxeof (struct usb_ether*,struct usb_page_cache*,int,int,struct axe_sframe_hdr*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* le16toh (int) ; 
 struct axe_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int,struct axe_sframe_hdr*,int) ; 

__attribute__((used)) static int
axe_rx_frame(struct usb_ether *ue, struct usb_page_cache *pc, int actlen)
{
	struct axe_softc *sc;
	struct axe_sframe_hdr hdr;
	struct axe_csum_hdr csum_hdr;
	int error, len, pos;

	sc = uether_getsc(ue);
	pos = 0;
	len = 0;
	error = 0;
	if ((sc->sc_flags & AXE_FLAG_STD_FRAME) != 0) {
		while (pos < actlen) {
			if ((int)(pos + sizeof(hdr)) > actlen) {
				/* too little data */
				error = EINVAL;
				break;
			}
			usbd_copy_out(pc, pos, &hdr, sizeof(hdr));

			if ((hdr.len ^ hdr.ilen) != sc->sc_lenmask) {
				/* we lost sync */
				error = EINVAL;
				break;
			}
			pos += sizeof(hdr);
			len = le16toh(hdr.len);
			if (pos + len > actlen) {
				/* invalid length */
				error = EINVAL;
				break;
			}
			axe_rxeof(ue, pc, pos, len, NULL);
			pos += len + (len % 2);
		}
	} else if ((sc->sc_flags & AXE_FLAG_CSUM_FRAME) != 0) {
		while (pos < actlen) {
			if ((int)(pos + sizeof(csum_hdr)) > actlen) {
				/* too little data */
				error = EINVAL;
				break;
			}
			usbd_copy_out(pc, pos, &csum_hdr, sizeof(csum_hdr));

			csum_hdr.len = le16toh(csum_hdr.len);
			csum_hdr.ilen = le16toh(csum_hdr.ilen);
			csum_hdr.cstatus = le16toh(csum_hdr.cstatus);
			if ((AXE_CSUM_RXBYTES(csum_hdr.len) ^
			    AXE_CSUM_RXBYTES(csum_hdr.ilen)) !=
			    sc->sc_lenmask) {
				/* we lost sync */
				error = EINVAL;
				break;
			}
			/*
			 * Get total transferred frame length including
			 * checksum header.  The length should be multiple
			 * of 4.
			 */
			len = sizeof(csum_hdr) + AXE_CSUM_RXBYTES(csum_hdr.len);
			len = (len + 3) & ~3;
			if (pos + len > actlen) {
				/* invalid length */
				error = EINVAL;
				break;
			}
			axe_rxeof(ue, pc, pos + sizeof(csum_hdr),
			    AXE_CSUM_RXBYTES(csum_hdr.len), &csum_hdr);
			pos += len;
		}
	} else
		axe_rxeof(ue, pc, 0, actlen, NULL);

	if (error != 0)
		if_inc_counter(ue->ue_ifp, IFCOUNTER_IERRORS, 1);
	return (error);
}