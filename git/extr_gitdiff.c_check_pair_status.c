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
struct diff_filepair {int status; } ;

/* Variables and functions */
#define  DIFF_STATUS_UNKNOWN 128 
 int /*<<< orphan*/  die (char*) ; 

__attribute__((used)) static int check_pair_status(struct diff_filepair *p)
{
	switch (p->status) {
	case DIFF_STATUS_UNKNOWN:
		return 0;
	case 0:
		die("internal error in diff-resolve-rename-copy");
	default:
		return 1;
	}
}