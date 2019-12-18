#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {int /*<<< orphan*/  const oid; } ;
typedef  TYPE_1__ git_filter_source ;

/* Variables and functions */
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 

const git_oid *git_filter_source_id(const git_filter_source *src)
{
	return git_oid_is_zero(&src->oid) ? NULL : &src->oid;
}