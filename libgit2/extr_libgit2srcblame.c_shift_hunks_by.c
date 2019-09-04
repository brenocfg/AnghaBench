#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t length; scalar_t__* contents; } ;
typedef  TYPE_1__ git_vector ;
struct TYPE_6__ {int final_start_line_number; } ;
typedef  TYPE_2__ git_blame_hunk ;

/* Variables and functions */
 int /*<<< orphan*/  git_vector_bsearch2 (size_t*,TYPE_1__*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  hunk_byfinalline_search_cmp ; 

__attribute__((used)) static void shift_hunks_by(git_vector *v, size_t start_line, int shift_by)
{
	size_t i;

	if (!git_vector_bsearch2(&i, v, hunk_byfinalline_search_cmp, &start_line)) {
		for (; i < v->length; i++) {
			git_blame_hunk *hunk = (git_blame_hunk*)v->contents[i];
			hunk->final_start_line_number += shift_by;
		}
	}
}