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
typedef  int /*<<< orphan*/  u_char ;
struct fuzz {int strategy; int /*<<< orphan*/ * fuzzed; int /*<<< orphan*/  slen; int /*<<< orphan*/  o1; } ;

/* Variables and functions */
#define  FUZZ_1_BIT_FLIP 134 
#define  FUZZ_1_BYTE_FLIP 133 
#define  FUZZ_2_BIT_FLIP 132 
#define  FUZZ_2_BYTE_FLIP 131 
#define  FUZZ_BASE64 130 
#define  FUZZ_TRUNCATE_END 129 
#define  FUZZ_TRUNCATE_START 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 

u_char *
fuzz_ptr(struct fuzz *fuzz)
{
	assert(fuzz->fuzzed != NULL);
	switch (fuzz->strategy) {
	case FUZZ_1_BIT_FLIP:
	case FUZZ_2_BIT_FLIP:
	case FUZZ_1_BYTE_FLIP:
	case FUZZ_2_BYTE_FLIP:
	case FUZZ_BASE64:
		return fuzz->fuzzed;
	case FUZZ_TRUNCATE_START:
		assert(fuzz->o1 <= fuzz->slen);
		return fuzz->fuzzed + fuzz->o1;
	case FUZZ_TRUNCATE_END:
		assert(fuzz->o1 <= fuzz->slen);
		return fuzz->fuzzed;
	default:
		abort();
	}
}