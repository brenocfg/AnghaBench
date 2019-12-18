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
struct rcsection {int /*<<< orphan*/  rs_keys; } ;
struct rckey {void* rk_value; void* rk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rckey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 struct rckey* malloc (int) ; 
 struct rckey* rc_sect_findkey (struct rcsection*,char const*) ; 
 int /*<<< orphan*/  rk_next ; 
 void* strdup (char const*) ; 

__attribute__((used)) static struct rckey *
rc_sect_addkey(struct rcsection *rsp, const char *name, const char *value)
{
	struct rckey *p;

	p = rc_sect_findkey(rsp, name);
	if (p) {
		free(p->rk_value);
	} else {
		p = malloc(sizeof(*p));
		if (!p) return NULL;
		SLIST_INSERT_HEAD(&rsp->rs_keys, p, rk_next);
		p->rk_name = strdup(name);
	}
	p->rk_value = value ? strdup(value) : strdup("");
	return p;
}