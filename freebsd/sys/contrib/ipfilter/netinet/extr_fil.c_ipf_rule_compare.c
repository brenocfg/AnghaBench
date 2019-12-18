#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fr_cksum; scalar_t__ fr_size; scalar_t__ fr_dsize; char* fr_caddr; scalar_t__ fr_data; int /*<<< orphan*/  fr_ifnames; int /*<<< orphan*/  fr_func; } ;
typedef  TYPE_1__ frentry_t ;

/* Variables and functions */
 scalar_t__ FR_CMPSIZ ; 
 int FR_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ IPF_FRDEST_DIFFERENT (int /*<<< orphan*/ ) ; 
 scalar_t__ IPF_IFNAMES_DIFFERENT (int /*<<< orphan*/ ) ; 
 scalar_t__ bcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  fr_dif ; 
 int /*<<< orphan*/ * fr_ifnames ; 
 int /*<<< orphan*/  fr_rif ; 
 int /*<<< orphan*/  fr_tif ; 

__attribute__((used)) static int
ipf_rule_compare(frentry_t *fr1, frentry_t *fr2)
{
	int i;

	if (fr1->fr_cksum != fr2->fr_cksum)
		return (1);
	if (fr1->fr_size != fr2->fr_size)
		return (2);
	if (fr1->fr_dsize != fr2->fr_dsize)
		return (3);
	if (bcmp((char *)&fr1->fr_func, (char *)&fr2->fr_func, FR_CMPSIZ)
	    != 0)
		return (4);
	/*
	 * XXX:	There is still a bug here as different rules with the
	 *	the same interfaces but in a different order will compare
	 *	differently. But since multiple interfaces in a rule doesn't
	 *	work anyway a simple straightforward compare is performed
	 *	here. Ultimately frentry_t creation will need to be
	 *	revisited in ipf_y.y. While the other issue, recognition
	 *	of only the first interface in a list of interfaces will
	 *	need to be separately addressed along with why only four.
	 */
	for (i = 0; i < FR_NUM(fr1->fr_ifnames); i++) {
		/*
		 * XXX:	It's either the same index or uninitialized.
		 * 	We assume this because multiple interfaces
		 *	referenced by the same rule doesn't work anyway.
		 */
		if (IPF_IFNAMES_DIFFERENT(fr_ifnames[i]))
			return(5);
	}

	if (IPF_FRDEST_DIFFERENT(fr_tif))
		return (6);
	if (IPF_FRDEST_DIFFERENT(fr_rif))
		return (7);
	if (IPF_FRDEST_DIFFERENT(fr_dif))
		return (8);
	if (!fr1->fr_data && !fr2->fr_data)
		return (0);	/* move along, nothing to see here */
	if (fr1->fr_data && fr2->fr_data) {
		if (bcmp(fr1->fr_caddr, fr2->fr_caddr, fr1->fr_dsize) == 0)
			return (0);	/* same */
	}
	return (9);
}