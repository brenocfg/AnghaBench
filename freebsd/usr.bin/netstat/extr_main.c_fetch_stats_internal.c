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
typedef  scalar_t__ u_long ;
typedef  int (* kreadfn_t ) (scalar_t__,void*,size_t) ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 scalar_t__ live ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int sysctlbyname (char const*,void*,size_t*,void*,size_t) ; 
 int /*<<< orphan*/  xo_warn (char*,char const*) ; 

__attribute__((used)) static int
fetch_stats_internal(const char *sysctlname, u_long off, void *stats,
    size_t len, kreadfn_t kreadfn, int zero)
{
	int error;

	if (live) {
		memset(stats, 0, len);
		if (zero)
			error = sysctlbyname(sysctlname, NULL, NULL, stats,
			    len);
		else
			error = sysctlbyname(sysctlname, stats, &len, NULL, 0);
		if (error == -1 && errno != ENOENT)
			xo_warn("sysctl %s", sysctlname);
	} else {
		if (off == 0)
			return (1);
		error = kreadfn(off, stats, len);
	}
	return (error);
}