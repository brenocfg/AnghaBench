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
struct netmap_priv_d {int np_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nm_os_get_module () ; 
 struct netmap_priv_d* nm_os_malloc (int) ; 

struct netmap_priv_d*
netmap_priv_new(void)
{
	struct netmap_priv_d *priv;

	priv = nm_os_malloc(sizeof(struct netmap_priv_d));
	if (priv == NULL)
		return NULL;
	priv->np_refs = 1;
	nm_os_get_module();
	return priv;
}