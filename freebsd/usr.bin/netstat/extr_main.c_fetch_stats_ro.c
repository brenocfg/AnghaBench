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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  kreadfn_t ;

/* Variables and functions */
 int fetch_stats_internal (char const*,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fetch_stats_ro(const char *sysctlname, u_long off, void *stats,
    size_t len, kreadfn_t kreadfn)
{

	return (fetch_stats_internal(sysctlname, off, stats, len, kreadfn, 0));
}