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
struct mbuf {int dummy; } ;
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_TYPE_EQUAL ; 
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  mls_set_effective (struct mac_mls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mls_netinet_firewall_send(struct mbuf *m, struct label *mlabel)
{
	struct mac_mls *dest;

	dest = SLOT(mlabel);

	/* XXX: where is the label for the firewall really coming from? */
	mls_set_effective(dest, MAC_MLS_TYPE_EQUAL, 0, NULL);
}