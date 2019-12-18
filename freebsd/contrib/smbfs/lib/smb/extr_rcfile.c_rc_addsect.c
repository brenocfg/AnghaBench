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
struct rcsection {int /*<<< orphan*/  rs_keys; int /*<<< orphan*/  rs_name; } ;
struct rcfile {int /*<<< orphan*/  rf_sect; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rcsection*,int /*<<< orphan*/ ) ; 
 struct rcsection* malloc (int) ; 
 struct rcsection* rc_findsect (struct rcfile*,char const*) ; 
 int /*<<< orphan*/  rs_next ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static struct rcsection *
rc_addsect(struct rcfile *rcp, const char *sectname)
{
	struct rcsection *p;

	p = rc_findsect(rcp, sectname);
	if (p) return p;
	p = malloc(sizeof(*p));
	if (!p) return NULL;
	p->rs_name = strdup(sectname);
	SLIST_INIT(&p->rs_keys);
	SLIST_INSERT_HEAD(&rcp->rf_sect, p, rs_next);
	return p;
}