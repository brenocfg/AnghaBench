#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ref_cache* cache; } ;
struct TYPE_4__ {TYPE_1__ subdir; } ;
struct ref_entry {int flag; TYPE_2__ u; } ;
struct ref_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct ref_entry*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int REF_DIR ; 
 int REF_INCOMPLETE ; 
 int /*<<< orphan*/  name ; 

struct ref_entry *create_dir_entry(struct ref_cache *cache,
				   const char *dirname, size_t len,
				   int incomplete)
{
	struct ref_entry *direntry;

	FLEX_ALLOC_MEM(direntry, name, dirname, len);
	direntry->u.subdir.cache = cache;
	direntry->flag = REF_DIR | (incomplete ? REF_INCOMPLETE : 0);
	return direntry;
}