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
struct stat_validity {scalar_t__ sd; } ;
struct stat_data {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_stat_data (scalar_t__,struct stat*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  stat_validity_clear (struct stat_validity*) ; 
 scalar_t__ xcalloc (int,int) ; 

void stat_validity_update(struct stat_validity *sv, int fd)
{
	struct stat st;

	if (fstat(fd, &st) < 0 || !S_ISREG(st.st_mode))
		stat_validity_clear(sv);
	else {
		if (!sv->sd)
			sv->sd = xcalloc(1, sizeof(struct stat_data));
		fill_stat_data(sv->sd, &st);
	}
}