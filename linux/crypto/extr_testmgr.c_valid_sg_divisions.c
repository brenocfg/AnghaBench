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
struct test_sg_division {scalar_t__ proportion_of_total; scalar_t__ flush_type; scalar_t__ nosimd; } ;
typedef  int /*<<< orphan*/  divs ;

/* Variables and functions */
 scalar_t__ FLUSH_TYPE_NONE ; 
 int SGDIVS_HAVE_FLUSHES ; 
 int SGDIVS_HAVE_NOSIMD ; 
 unsigned int TEST_SG_TOTAL ; 
 int /*<<< orphan*/ * memchr_inv (struct test_sg_division const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool valid_sg_divisions(const struct test_sg_division *divs,
			       unsigned int count, int *flags_ret)
{
	unsigned int total = 0;
	unsigned int i;

	for (i = 0; i < count && total != TEST_SG_TOTAL; i++) {
		if (divs[i].proportion_of_total <= 0 ||
		    divs[i].proportion_of_total > TEST_SG_TOTAL - total)
			return false;
		total += divs[i].proportion_of_total;
		if (divs[i].flush_type != FLUSH_TYPE_NONE)
			*flags_ret |= SGDIVS_HAVE_FLUSHES;
		if (divs[i].nosimd)
			*flags_ret |= SGDIVS_HAVE_NOSIMD;
	}
	return total == TEST_SG_TOTAL &&
		memchr_inv(&divs[i], 0, (count - i) * sizeof(divs[0])) == NULL;
}