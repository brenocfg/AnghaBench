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
struct name_cache {int dummy; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 char const* lookup_name (struct name_cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_uname_helper ; 

__attribute__((used)) static const char *
lookup_uname(void *data, int64_t uid)
{
	struct name_cache *uname_cache = (struct name_cache *)data;
	return (lookup_name(uname_cache,
		    &lookup_uname_helper, (id_t)uid));
}