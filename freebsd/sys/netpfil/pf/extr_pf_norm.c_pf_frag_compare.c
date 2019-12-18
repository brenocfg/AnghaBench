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
struct pf_fragment {int fr_id; int fr_proto; int fr_af; int /*<<< orphan*/  fr_dst; int /*<<< orphan*/  fr_src; } ;

/* Variables and functions */
 int pf_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pf_frag_compare(struct pf_fragment *a, struct pf_fragment *b)
{
	int	diff;

	if ((diff = a->fr_id - b->fr_id) != 0)
		return (diff);
	if ((diff = a->fr_proto - b->fr_proto) != 0)
		return (diff);
	if ((diff = a->fr_af - b->fr_af) != 0)
		return (diff);
	if ((diff = pf_addr_cmp(&a->fr_src, &b->fr_src, a->fr_af)) != 0)
		return (diff);
	if ((diff = pf_addr_cmp(&a->fr_dst, &b->fr_dst, a->fr_af)) != 0)
		return (diff);
	return (0);
}