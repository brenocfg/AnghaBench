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
typedef  scalar_t__ uint32_t ;
struct csrreg {scalar_t__ key; scalar_t__ val; } ;
struct crom_context {scalar_t__ depth; } ;

/* Variables and functions */
 scalar_t__ CSRKEY_SPEC ; 
 scalar_t__ CSRKEY_VER ; 
 struct csrreg* crom_get (struct crom_context*) ; 
 int /*<<< orphan*/  crom_init_context (struct crom_context*,scalar_t__*) ; 
 int /*<<< orphan*/  crom_next (struct crom_context*) ; 

int
crom_has_specver(uint32_t *p, uint32_t spec, uint32_t ver)
{
	struct csrreg *reg;
	struct crom_context c, *cc;
	int state = 0;

	cc = &c;
	crom_init_context(cc, p);
	while (cc->depth >= 0) {
		reg = crom_get(cc);
		if (state == 0) {
			if (reg->key == CSRKEY_SPEC && reg->val == spec)
				state = 1;
			else
				state = 0;
		} else {
			if (reg->key == CSRKEY_VER && reg->val == ver)
				return 1;
			else
				state = 0;
		}
		crom_next(cc);
	}
	return 0;
}