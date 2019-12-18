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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_2__ {size_t total; int /*<<< orphan*/  const** parents; } ;
typedef  TYPE_1__ commit_parent_oids ;

/* Variables and functions */

__attribute__((used)) static const git_oid *commit_parent_from_ids(size_t curr, void *payload)
{
	commit_parent_oids *data = payload;
	return (curr < data->total) ? data->parents[curr] : NULL;
}