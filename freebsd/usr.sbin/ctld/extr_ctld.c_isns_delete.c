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
struct isns {int /*<<< orphan*/ * i_ai; struct isns* i_addr; TYPE_1__* i_conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  conf_isns; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct isns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct isns*) ; 
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_next ; 

void
isns_delete(struct isns *isns)
{

	TAILQ_REMOVE(&isns->i_conf->conf_isns, isns, i_next);
	free(isns->i_addr);
	if (isns->i_ai != NULL)
		freeaddrinfo(isns->i_ai);
	free(isns);
}