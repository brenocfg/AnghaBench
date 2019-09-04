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
struct ident_split {int /*<<< orphan*/  name_end; int /*<<< orphan*/  name_begin; int /*<<< orphan*/  mail_end; int /*<<< orphan*/  mail_begin; } ;

/* Variables and functions */
 int buf_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ident_cmp(const struct ident_split *a,
	      const struct ident_split *b)
{
	int cmp;

	cmp = buf_cmp(a->mail_begin, a->mail_end,
		      b->mail_begin, b->mail_end);
	if (cmp)
		return cmp;

	return buf_cmp(a->name_begin, a->name_end,
		       b->name_begin, b->name_end);
}