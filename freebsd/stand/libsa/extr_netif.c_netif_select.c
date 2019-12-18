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
struct netif_driver {int netif_nifs; char* netif_bname; TYPE_1__* netif_ifs; } ;
struct netif {int nif_unit; int nif_sel; struct netif_driver* nif_driver; } ;
struct TYPE_2__ {int dif_nsel; int dif_used; } ;

/* Variables and functions */
 scalar_t__ netif_debug ; 
 struct netif_driver** netif_drivers ; 
 int netif_match (struct netif*,void*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

struct netif *
netif_select(void *machdep_hint)
{
	int d, u, unit_done, s;
	struct netif_driver *drv;
	struct netif cur_if;
	static struct netif best_if;
	int best_val;
	int val;

	best_val = 0;
	best_if.nif_driver = NULL;

	for (d = 0; netif_drivers[d] != NULL; d++) {
		cur_if.nif_driver = netif_drivers[d];
		drv = cur_if.nif_driver;

		for (u = 0; u < drv->netif_nifs; u++) {
			cur_if.nif_unit = u;
			unit_done = 0;
		
#ifdef NETIF_DEBUG
			if (netif_debug)
				printf("\t%s%d:", drv->netif_bname,
				    cur_if.nif_unit);
#endif

			for (s = 0; s < drv->netif_ifs[u].dif_nsel; s++) {
				cur_if.nif_sel = s;

				if (drv->netif_ifs[u].dif_used & (1 << s)) {
#ifdef NETIF_DEBUG
					if (netif_debug)
						printf(" [%d used]", s);
#endif
					continue;
				}

				val = netif_match(&cur_if, machdep_hint);
#ifdef NETIF_DEBUG
				if (netif_debug)
					printf(" [%d -> %d]", s, val);
#endif
				if (val > best_val) {
					best_val = val;
					best_if = cur_if;
				}
			}
#ifdef NETIF_DEBUG
			if (netif_debug)
				printf("\n");
#endif
		}
	}

	if (best_if.nif_driver == NULL)
		return NULL;

	best_if.nif_driver->
	    netif_ifs[best_if.nif_unit].dif_used |= (1 << best_if.nif_sel);

#ifdef NETIF_DEBUG
	if (netif_debug)
		printf("netif_select: %s%d(%d) wins\n",
			best_if.nif_driver->netif_bname,
			best_if.nif_unit, best_if.nif_sel);
#endif
	return &best_if;
}