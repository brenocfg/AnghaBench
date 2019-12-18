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
struct inpcb {int dummy; } ;

/* Variables and functions */
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  mls_copy_effective (struct mac_mls*,struct mac_mls*) ; 

__attribute__((used)) static void
mls_inpcb_create_mbuf(struct inpcb *inp, struct label *inplabel,
    struct mbuf *m, struct label *mlabel)
{
	struct mac_mls *source, *dest;

	source = SLOT(inplabel);
	dest = SLOT(mlabel);

	mls_copy_effective(source, dest);
}