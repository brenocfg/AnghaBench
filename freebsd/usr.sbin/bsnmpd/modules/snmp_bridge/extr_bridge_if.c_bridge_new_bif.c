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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  octet; } ;
struct bridge_if {int hold_time; int /*<<< orphan*/  prot_spec; int /*<<< orphan*/  br_type; int /*<<< orphan*/  sysindex; TYPE_1__ br_addr; int /*<<< orphan*/  bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BaseType_transparent_only ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_ifs ; 
 int /*<<< orphan*/  bridge_ifs_insert (int /*<<< orphan*/ *,struct bridge_if*) ; 
 int /*<<< orphan*/  bzero (struct bridge_if*,int) ; 
 int /*<<< orphan*/  dot1dStpProtocolSpecification_ieee8021d ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bridge_if *
bridge_new_bif(const char *bif_n, uint32_t sysindex, const u_char *physaddr)
{
	struct bridge_if *bif;

	if ((bif = (struct bridge_if *) malloc(sizeof(*bif)))== NULL) {
		syslog(LOG_ERR, "bridge new interface failed: %s",
		    strerror(errno));
		return (NULL);
	}

	bzero(bif, sizeof(struct bridge_if));
	strlcpy(bif->bif_name, bif_n, IFNAMSIZ);
	bcopy(physaddr, bif->br_addr.octet, ETHER_ADDR_LEN);
	bif->sysindex = sysindex;
	bif->br_type = BaseType_transparent_only;
	/* 1 - all bridges default hold time * 100 - centi-seconds */
	bif->hold_time = 1 * 100;
	bif->prot_spec = dot1dStpProtocolSpecification_ieee8021d;
	bridge_ifs_insert(&bridge_ifs, bif);

	return (bif);
}