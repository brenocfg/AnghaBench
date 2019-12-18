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
nlmtonlm4(struct nlm_lock *arg, struct nlm4_lock *arg4)
{
	arg4->caller_name = arg->caller_name;
	arg4->fh = arg->fh;
	arg4->oh = arg->oh;
	arg4->svid = arg->svid;
	arg4->l_offset = arg->l_offset;
	arg4->l_len = arg->l_len;
}