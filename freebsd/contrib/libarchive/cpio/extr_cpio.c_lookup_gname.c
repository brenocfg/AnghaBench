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
struct cpio {int /*<<< orphan*/  gname_cache; } ;
typedef  int /*<<< orphan*/  id_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  lookup_gname_helper ; 
 char const* lookup_name (struct cpio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
lookup_gname(struct cpio *cpio, gid_t gid)
{
	return (lookup_name(cpio, &cpio->gname_cache,
		    &lookup_gname_helper, (id_t)gid));
}