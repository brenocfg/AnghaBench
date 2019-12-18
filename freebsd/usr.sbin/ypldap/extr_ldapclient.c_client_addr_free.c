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
struct ypldap_addr {int dummy; } ;
struct idm {int /*<<< orphan*/  idm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ypldap_addr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ypldap_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ypldap_addr*) ; 
 int /*<<< orphan*/  next ; 

int
client_addr_free(struct idm *idm)
{
        struct ypldap_addr         *h;

	while (!TAILQ_EMPTY(&idm->idm_addr)) {
		h = TAILQ_FIRST(&idm->idm_addr);
		TAILQ_REMOVE(&idm->idm_addr, h, next);
		free(h);
	}

	return (0);
}