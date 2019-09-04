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
struct stat_validity {int /*<<< orphan*/ * sd; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_stat_data (int /*<<< orphan*/ *,struct stat*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int stat_validity_check(struct stat_validity *sv, const char *path)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return sv->sd == NULL;
	if (!sv->sd)
		return 0;
	return S_ISREG(st.st_mode) && !match_stat_data(sv->sd, &st);
}