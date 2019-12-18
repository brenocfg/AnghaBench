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
struct gmesh {struct gident* lg_ident; } ;
struct gident {void const* lg_id; } ;

/* Variables and functions */

struct gident *
geom_lookupid(struct gmesh *gmp, const void *id)
{
	struct gident *gip;

	for (gip = gmp->lg_ident; gip->lg_id != NULL; gip++)
		if (gip->lg_id == id)
			return (gip);
	return (NULL);
}