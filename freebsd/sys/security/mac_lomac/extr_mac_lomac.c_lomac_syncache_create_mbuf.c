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
struct mac_lomac {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  lomac_copy (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static void
lomac_syncache_create_mbuf(struct label *sc_label, struct mbuf *m,
    struct label *mlabel)
{
	struct mac_lomac *source, *dest;

	source = SLOT(sc_label);
	dest = SLOT(mlabel);
	lomac_copy(source, dest);
}