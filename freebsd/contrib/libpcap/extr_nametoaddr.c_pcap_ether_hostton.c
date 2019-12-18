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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_etherent {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ETHERS_FILE ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct pcap_etherent* pcap_next_etherent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

u_char *
pcap_ether_hostton(const char *name)
{
	register struct pcap_etherent *ep;
	register u_char *ap;
	static FILE *fp = NULL;
	static int init = 0;

	if (!init) {
		fp = fopen(PCAP_ETHERS_FILE, "r");
		++init;
		if (fp == NULL)
			return (NULL);
	} else if (fp == NULL)
		return (NULL);
	else
		rewind(fp);

	while ((ep = pcap_next_etherent(fp)) != NULL) {
		if (strcmp(ep->name, name) == 0) {
			ap = (u_char *)malloc(6);
			if (ap != NULL) {
				memcpy(ap, ep->addr, 6);
				return (ap);
			}
			break;
		}
	}
	return (NULL);
}