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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int git_revwalk_hide (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int push_commit(git_revwalk *walk, const git_oid *oid, int hide)
{
	if (hide)
		return git_revwalk_hide(walk, oid);
	else
		return git_revwalk_push(walk, oid);
}