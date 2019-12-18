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
struct ether_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSPRINT ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int RV_NOENUM ; 
 int RV_NOTFOUND ; 
 int RV_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 struct ether_addr* ether_aton (char*) ; 
 scalar_t__ ether_hostton (char*,struct ether_addr*) ; 
 scalar_t__ ether_ntohost (char*,struct ether_addr*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
ethers(int argc, char *argv[])
{
	char		hostname[MAXHOSTNAMELEN + 1], *hp;
	struct ether_addr ea, *eap;
	int		i, rv;

	assert(argc > 1);
	assert(argv != NULL);

#define ETHERSPRINT	printf("%-17s  %s\n", ether_ntoa(eap), hp)

	rv = RV_OK;
	if (argc == 2) {
		fprintf(stderr, "Enumeration not supported on ethers\n");
		rv = RV_NOENUM;
	} else {
		for (i = 2; i < argc; i++) {
			if ((eap = ether_aton(argv[i])) == NULL) {
				eap = &ea;
				hp = argv[i];
				if (ether_hostton(hp, eap) != 0) {
					rv = RV_NOTFOUND;
					break;
				}
			} else {
				hp = hostname;
				if (ether_ntohost(hp, eap) != 0) {
					rv = RV_NOTFOUND;
					break;
				}
			}
			ETHERSPRINT;
		}
	}
	return rv;
}