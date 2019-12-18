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
struct mac_lomac {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 scalar_t__ lomac_equal_single (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_socket_check_deliver(struct socket *so, struct label *solabel,
    struct mbuf *m, struct label *mlabel)
{
	struct mac_lomac *p, *s;
	int error;

	if (!lomac_enabled)
		return (0);

	p = SLOT(mlabel);
	s = SLOT(solabel);

	SOCK_LOCK(so);
	error = lomac_equal_single(p, s) ? 0 : EACCES;
	SOCK_UNLOCK(so);
	return (error);
}