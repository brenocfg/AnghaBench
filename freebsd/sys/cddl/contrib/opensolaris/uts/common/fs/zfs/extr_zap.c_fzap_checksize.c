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
typedef  int uint64_t ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZAP_MAXVALUELEN ; 

__attribute__((used)) static int
fzap_checksize(uint64_t integer_size, uint64_t num_integers)
{
	/* Only integer sizes supported by C */
	switch (integer_size) {
	case 1:
	case 2:
	case 4:
	case 8:
		break;
	default:
		return (SET_ERROR(EINVAL));
	}

	if (integer_size * num_integers > ZAP_MAXVALUELEN)
		return (E2BIG);

	return (0);
}