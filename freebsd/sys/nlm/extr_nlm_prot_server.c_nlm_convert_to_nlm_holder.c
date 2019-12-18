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
struct nlm_holder {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  oh; int /*<<< orphan*/  svid; int /*<<< orphan*/  exclusive; } ;
struct nlm4_holder {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  oh; int /*<<< orphan*/  svid; int /*<<< orphan*/  exclusive; } ;

/* Variables and functions */

__attribute__((used)) static void
nlm_convert_to_nlm_holder(struct nlm_holder *dst, struct nlm4_holder *src)
{

	dst->exclusive = src->exclusive;
	dst->svid = src->svid;
	dst->oh = src->oh;
	dst->l_offset = src->l_offset;
	dst->l_len = src->l_len;
}