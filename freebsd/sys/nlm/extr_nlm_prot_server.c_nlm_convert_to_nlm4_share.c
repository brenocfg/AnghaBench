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
struct nlm_share {int /*<<< orphan*/  access; int /*<<< orphan*/  mode; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;
struct nlm4_share {int /*<<< orphan*/  access; int /*<<< orphan*/  mode; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;

/* Variables and functions */

__attribute__((used)) static void
nlm_convert_to_nlm4_share(struct nlm4_share *dst, struct nlm_share *src)
{

	dst->caller_name = src->caller_name;
	dst->fh = src->fh;
	dst->oh = src->oh;
	dst->mode = src->mode;
	dst->access = src->access;
}