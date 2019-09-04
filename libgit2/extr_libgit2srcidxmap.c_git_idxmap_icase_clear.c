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
typedef  int /*<<< orphan*/  git_idxmap_icase ;

/* Variables and functions */
 int /*<<< orphan*/  idxicase ; 
 int /*<<< orphan*/  kh_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void git_idxmap_icase_clear(git_idxmap_icase *map)
{
	kh_clear(idxicase, map);
}