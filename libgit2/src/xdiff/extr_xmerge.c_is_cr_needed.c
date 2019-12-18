#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i2; scalar_t__ i1; } ;
typedef  TYPE_1__ xdmerge_t ;
struct TYPE_7__ {int /*<<< orphan*/  xdf1; int /*<<< orphan*/  xdf2; } ;
typedef  TYPE_2__ xdfenv_t ;

/* Variables and functions */
 int is_eol_crlf (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int is_cr_needed(xdfenv_t *xe1, xdfenv_t *xe2, xdmerge_t *m)
{
	int needs_cr;

	/* Match post-images' preceding, or first, lines' end-of-line style */
	needs_cr = is_eol_crlf(&xe1->xdf2, m->i1 ? m->i1 - 1 : 0);
	if (needs_cr)
		needs_cr = is_eol_crlf(&xe2->xdf2, m->i2 ? m->i2 - 1 : 0);
	/* Look at pre-image's first line, unless we already settled on LF */
	if (needs_cr)
		needs_cr = is_eol_crlf(&xe1->xdf1, 0);
	/* If still undecided, use LF-only */
	return needs_cr < 0 ? 0 : needs_cr;
}