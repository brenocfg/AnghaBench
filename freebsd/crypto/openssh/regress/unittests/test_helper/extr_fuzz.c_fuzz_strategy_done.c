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
struct fuzz {int strategy; int o1; int o2; int slen; } ;

/* Variables and functions */
#define  FUZZ_1_BIT_FLIP 134 
#define  FUZZ_1_BYTE_FLIP 133 
#define  FUZZ_2_BIT_FLIP 132 
#define  FUZZ_2_BYTE_FLIP 131 
#define  FUZZ_BASE64 130 
 int /*<<< orphan*/  FUZZ_DBG (char*) ; 
#define  FUZZ_TRUNCATE_END 129 
#define  FUZZ_TRUNCATE_START 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fuzz_ntop (int) ; 

__attribute__((used)) static int
fuzz_strategy_done(struct fuzz *fuzz)
{
	FUZZ_DBG(("fuzz = %p, strategy = %s, o1 = %zu, o2 = %zu, slen = %zu",
	    fuzz, fuzz_ntop(fuzz->strategy), fuzz->o1, fuzz->o2, fuzz->slen));

	switch (fuzz->strategy) {
	case FUZZ_1_BIT_FLIP:
		return fuzz->o1 >= fuzz->slen * 8;
	case FUZZ_2_BIT_FLIP:
		return fuzz->o2 >= fuzz->slen * 8;
	case FUZZ_2_BYTE_FLIP:
		return fuzz->o2 >= fuzz->slen;
	case FUZZ_1_BYTE_FLIP:
	case FUZZ_TRUNCATE_START:
	case FUZZ_TRUNCATE_END:
	case FUZZ_BASE64:
		return fuzz->o1 >= fuzz->slen;
	default:
		abort();
	}
}