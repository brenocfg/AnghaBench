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
struct socket {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  biba_copy_effective (struct mac_biba*,struct mac_biba*) ; 

__attribute__((used)) static void
biba_inpcb_create(struct socket *so, struct label *solabel,
    struct inpcb *inp, struct label *inplabel)
{
	struct mac_biba *source, *dest;

	source = SLOT(solabel);
	dest = SLOT(inplabel);

	SOCK_LOCK(so);
	biba_copy_effective(source, dest);
	SOCK_UNLOCK(so);
}