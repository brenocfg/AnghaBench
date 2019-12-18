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
struct mbuf {int dummy; } ;
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  mls_copy_effective (struct mac_mls*,struct mac_mls*) ; 

__attribute__((used)) static void
mls_socketpeer_set_from_mbuf(struct mbuf *m, struct label *mlabel,
    struct socket *so, struct label *sopeerlabel)
{
	struct mac_mls *source, *dest;

	source = SLOT(mlabel);
	dest = SLOT(sopeerlabel);

	SOCK_LOCK(so);
	mls_copy_effective(source, dest);
	SOCK_UNLOCK(so);
}