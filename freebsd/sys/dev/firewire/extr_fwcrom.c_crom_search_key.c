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
typedef  scalar_t__ uint8_t ;
struct csrreg {scalar_t__ key; } ;
struct crom_context {scalar_t__ depth; } ;

/* Variables and functions */
 struct csrreg* crom_get (struct crom_context*) ; 
 int /*<<< orphan*/  crom_next (struct crom_context*) ; 

struct csrreg *
crom_search_key(struct crom_context *cc, uint8_t key)
{
	struct csrreg *reg;

	while (cc->depth >= 0) {
		reg = crom_get(cc);
		if (reg->key == key)
			return reg;
		crom_next(cc);
	}
	return NULL;
}