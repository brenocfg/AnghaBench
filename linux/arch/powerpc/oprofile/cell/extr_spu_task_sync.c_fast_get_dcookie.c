#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct TYPE_2__ {int d_flags; } ;

/* Variables and functions */
 int DCACHE_COOKIE ; 
 int /*<<< orphan*/  get_dcookie (struct path const*,unsigned long*) ; 

__attribute__((used)) static inline unsigned long fast_get_dcookie(const struct path *path)
{
	unsigned long cookie;

	if (path->dentry->d_flags & DCACHE_COOKIE)
		return (unsigned long)path->dentry;
	get_dcookie(path, &cookie);
	return cookie;
}