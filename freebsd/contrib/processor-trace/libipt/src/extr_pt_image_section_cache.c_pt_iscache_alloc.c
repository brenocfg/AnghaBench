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
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 struct pt_image_section_cache* malloc (int) ; 
 int /*<<< orphan*/  pt_iscache_init (struct pt_image_section_cache*,char const*) ; 

struct pt_image_section_cache *pt_iscache_alloc(const char *name)
{
	struct pt_image_section_cache *iscache;

	iscache = malloc(sizeof(*iscache));
	if (iscache)
		pt_iscache_init(iscache, name);

	return iscache;
}