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
struct ipfw_sopt_handler {int /*<<< orphan*/  handler; int /*<<< orphan*/  version; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL3_LOCK () ; 
 int /*<<< orphan*/  CTL3_UNLOCK () ; 
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  ctl3_gencnt ; 
 struct ipfw_sopt_handler* ctl3_handlers ; 
 int ctl3_hsize ; 
 struct ipfw_sopt_handler* find_sh (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ipfw_sopt_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ipfw_sopt_handler*,struct ipfw_sopt_handler*,size_t) ; 

int
ipfw_del_sopt_handler(struct ipfw_sopt_handler *sh, size_t count)
{
	size_t sz;
	struct ipfw_sopt_handler *tmp, *h;
	int i;

	CTL3_LOCK();

	for (i = 0; i < count; i++) {
		tmp = &sh[i];
		h = find_sh(tmp->opcode, tmp->version, tmp->handler);
		if (h == NULL)
			continue;

		sz = (ctl3_handlers + ctl3_hsize - (h + 1)) * sizeof(*h);
		memmove(h, h + 1, sz);
		ctl3_hsize--;
	}

	if (ctl3_hsize == 0) {
		if (ctl3_handlers != NULL)
			free(ctl3_handlers, M_IPFW);
		ctl3_handlers = NULL;
	}

	ctl3_gencnt++;

	CTL3_UNLOCK();

	return (0);
}