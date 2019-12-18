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
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * manufacturer; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 

int p2p_set_manufacturer(struct p2p_data *p2p, const char *manufacturer)
{
	os_free(p2p->cfg->manufacturer);
	p2p->cfg->manufacturer = NULL;
	if (manufacturer) {
		p2p->cfg->manufacturer = os_strdup(manufacturer);
		if (p2p->cfg->manufacturer == NULL)
			return -1;
	}

	return 0;
}