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
struct glob_path_stat {int /*<<< orphan*/  gps_path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_gps(const void *_p, const void *_q)
{
	const struct glob_path_stat *p = (const struct glob_path_stat *)_p;
	const struct glob_path_stat *q = (const struct glob_path_stat *)_q;

	return(strcmp(p->gps_path, q->gps_path));
}