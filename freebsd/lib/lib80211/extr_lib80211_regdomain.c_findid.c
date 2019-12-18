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
struct regdata {struct ident* ident; } ;
struct ident {void* p; int /*<<< orphan*/ * id; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,void const*) ; 

__attribute__((used)) static void *
findid(struct regdata *rdp, const void *id, int type)
{
	struct ident *ip;

	for (ip = rdp->ident; ip->id != NULL; ip++)
		if ((int) ip->type == type && strcasecmp(ip->id, id) == 0)
			return ip->p;
	return NULL;
}