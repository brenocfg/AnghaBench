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
struct rerere_dir {int status_nr; scalar_t__ status; int /*<<< orphan*/  status_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,int) ; 

__attribute__((used)) static void fit_variant(struct rerere_dir *rr_dir, int variant)
{
	variant++;
	ALLOC_GROW(rr_dir->status, variant, rr_dir->status_alloc);
	if (rr_dir->status_nr < variant) {
		memset(rr_dir->status + rr_dir->status_nr,
		       '\0', variant - rr_dir->status_nr);
		rr_dir->status_nr = variant;
	}
}