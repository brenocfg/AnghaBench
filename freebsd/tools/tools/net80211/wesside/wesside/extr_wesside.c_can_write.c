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
struct TYPE_4__ {int /*<<< orphan*/  cipher; } ;
struct TYPE_3__ {int /*<<< orphan*/  prga; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REQUEST ; 
#define  FOUND_VICTIM 130 
#define  GOT_ASSOC 129 
#define  GOT_AUTH 128 
 int SENDING_ASSOC ; 
 int SENDING_AUTH ; 
 int /*<<< orphan*/  arpsend ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  decrypt (int) ; 
 TYPE_2__ decryptstate ; 
 int /*<<< orphan*/  discover_prga (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  flood_inet (int) ; 
 int /*<<< orphan*/  floodip ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min_prga ; 
 int /*<<< orphan*/  myip ; 
 int /*<<< orphan*/  mymac ; 
 char* netip ; 
 int /*<<< orphan*/  netip_arg ; 
 TYPE_1__ prgainfo ; 
 unsigned char* rtrmac ; 
 int /*<<< orphan*/  send_arp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  send_assoc (int) ; 
 int /*<<< orphan*/  send_auth (int) ; 
 int /*<<< orphan*/  send_frame (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int state ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  taptx ; 
 int /*<<< orphan*/  taptx_len ; 
 int /*<<< orphan*/  time_print (char*,char*) ; 

void can_write(int tx) {
	static char arp_ip[16];

	switch (state) {
		case FOUND_VICTIM:
			send_auth(tx);
			state = SENDING_AUTH;
			break;

		case GOT_AUTH:
			send_assoc(tx);
			state = SENDING_ASSOC;
			break;

		case GOT_ASSOC:
			if (prgainfo.prga && prgainfo.len < min_prga) {
				discover_prga(tx);
				break;
			}
			
			if (decryptstate.cipher) {
				decrypt(tx);
				break;
			}
			
			if (!prgainfo.prga)
				break;

			if (taptx_len) {
				send_frame(tx, taptx, taptx_len);
				taptx_len = 0;
				break;
			}	

			// try to find rtr mac addr
			if (netip && !rtrmac) {
				char* ptr;

				strcpy(arp_ip, netip);
				if (!netip_arg) {
					ptr = strchr(arp_ip, '.');
					assert(ptr);
					ptr = strchr(++ptr, '.');
					assert(ptr);
					ptr = strchr(++ptr, '.');
					assert(ptr);
					strcpy(++ptr, "1");
				}

				if (gettimeofday(&arpsend, NULL) == -1)
					err(1, "gettimeofday()");

				time_print("Sending arp request for: %s\n", arp_ip);
				send_arp(tx, ARPOP_REQUEST, myip, mymac,
					 arp_ip, "\x00\x00\x00\x00\x00\x00");
			
				// XXX lame
				rtrmac = (unsigned char*)1;
				break;	 
			}
	
			// need to generate traffic...
			if (rtrmac > (unsigned char*)1 && netip) {
				if (floodip)
					flood_inet(tx);
				else {
					// XXX lame technique... anyway... im
					// only interested in flood_inet...

					// could ping broadcast....
					send_arp(tx, ARPOP_REQUEST, myip, mymac,
						 arp_ip, "\x00\x00\x00\x00\x00\x00");
				}

				break;
			}

			break;	
	}
}