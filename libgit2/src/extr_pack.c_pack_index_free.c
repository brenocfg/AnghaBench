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
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct git_pack_file {TYPE_1__ index_map; int /*<<< orphan*/ * oids; } ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_mmap_free (TYPE_1__*) ; 

__attribute__((used)) static void pack_index_free(struct git_pack_file *p)
{
	if (p->oids) {
		git__free(p->oids);
		p->oids = NULL;
	}
	if (p->index_map.data) {
		git_futils_mmap_free(&p->index_map);
		p->index_map.data = NULL;
	}
}