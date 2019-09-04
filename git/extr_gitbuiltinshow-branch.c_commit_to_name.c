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
struct commit_name {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct commit_name** commit_name_slab_at (int /*<<< orphan*/ *,struct commit*) ; 
 int /*<<< orphan*/  name_slab ; 

__attribute__((used)) static struct commit_name *commit_to_name(struct commit *commit)
{
	return *commit_name_slab_at(&name_slab, commit);
}