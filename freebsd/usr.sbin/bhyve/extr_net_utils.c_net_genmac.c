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
typedef  int uint8_t ;
struct pci_devinst {int pi_slot; int pi_func; } ;
typedef  int /*<<< orphan*/  nstr ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* vmname ; 

void
net_genmac(struct pci_devinst *pi, uint8_t *macaddr)
{
	/*
	 * The default MAC address is the standard NetApp OUI of 00-a0-98,
	 * followed by an MD5 of the PCI slot/func number and dev name
	 */
	MD5_CTX mdctx;
	unsigned char digest[16];
	char nstr[80];

	snprintf(nstr, sizeof(nstr), "%d-%d-%s", pi->pi_slot,
	    pi->pi_func, vmname);

	MD5Init(&mdctx);
	MD5Update(&mdctx, nstr, (unsigned int)strlen(nstr));
	MD5Final(digest, &mdctx);

	macaddr[0] = 0x00;
	macaddr[1] = 0xa0;
	macaddr[2] = 0x98;
	macaddr[3] = digest[0];
	macaddr[4] = digest[1];
	macaddr[5] = digest[2];
}