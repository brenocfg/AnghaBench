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
struct mount {int dummy; } ;

/* Variables and functions */
 int fsess_opt_datacache (struct mount*) ; 

__attribute__((used)) static inline bool
fsess_opt_mmap(struct mount *mp)
{
	return (fsess_opt_datacache(mp));
}