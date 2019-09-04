#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  backends; } ;
typedef  TYPE_1__ git_config ;
struct TYPE_6__ {int /*<<< orphan*/  backend; } ;
typedef  TYPE_2__ backend_internal ;

/* Variables and functions */
 TYPE_2__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int find_next_backend(size_t *out, const git_config *cfg, size_t i)
{
	backend_internal *internal;

	for (; i > 0; --i) {
		internal = git_vector_get(&cfg->backends, i - 1);
		if (!internal || !internal->backend)
			continue;

		*out = i;
		return 0;
	}

	return -1;
}