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
struct nlm_lock {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;
struct nlm4_lock {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;

/* Variables and functions */

__attribute__((used)) static void
nlm_convert_to_nlm_lock(struct nlm_lock *dst, struct nlm4_lock *src)
{

	dst->caller_name = src->caller_name;
	dst->fh = src->fh;
	dst->oh = src->oh;
	dst->svid = src->svid;
	dst->l_offset = src->l_offset;
	dst->l_len = src->l_len;
}