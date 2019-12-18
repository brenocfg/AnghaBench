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
struct p2ps_advertisement {int /*<<< orphan*/  svc_name; struct p2ps_advertisement* next; } ;
struct p2p_data {struct p2ps_advertisement* p2ps_adv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2PS_WILD_HASH_STR ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ os_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p2p_wfa_service_adv(struct p2p_data *p2p)
{
	struct p2ps_advertisement *adv;

	for (adv = p2p->p2ps_adv_list; adv; adv = adv->next) {
		if (os_strncmp(adv->svc_name, P2PS_WILD_HASH_STR,
			       os_strlen(P2PS_WILD_HASH_STR)) == 0)
			return 1;
	}

	return 0;
}