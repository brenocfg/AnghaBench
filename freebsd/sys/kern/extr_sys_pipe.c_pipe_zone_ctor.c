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
struct pipe {void* pipe_present; struct pipepair* pipe_pair; struct pipe* pipe_peer; int /*<<< orphan*/  pipe_ctime; int /*<<< orphan*/  pipe_mtime; int /*<<< orphan*/  pipe_atime; } ;
struct pipepair {int /*<<< orphan*/ * pp_label; struct pipe pp_wpipe; struct pipe pp_rpipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 void* PIPE_ACTIVE ; 
 int /*<<< orphan*/  bzero (struct pipe*,int) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pipe_zone_ctor(void *mem, int size, void *arg, int flags)
{
	struct pipepair *pp;
	struct pipe *rpipe, *wpipe;

	KASSERT(size == sizeof(*pp), ("pipe_zone_ctor: wrong size"));

	pp = (struct pipepair *)mem;

	/*
	 * We zero both pipe endpoints to make sure all the kmem pointers
	 * are NULL, flag fields are zero'd, etc.  We timestamp both
	 * endpoints with the same time.
	 */
	rpipe = &pp->pp_rpipe;
	bzero(rpipe, sizeof(*rpipe));
	vfs_timestamp(&rpipe->pipe_ctime);
	rpipe->pipe_atime = rpipe->pipe_mtime = rpipe->pipe_ctime;

	wpipe = &pp->pp_wpipe;
	bzero(wpipe, sizeof(*wpipe));
	wpipe->pipe_ctime = rpipe->pipe_ctime;
	wpipe->pipe_atime = wpipe->pipe_mtime = rpipe->pipe_ctime;

	rpipe->pipe_peer = wpipe;
	rpipe->pipe_pair = pp;
	wpipe->pipe_peer = rpipe;
	wpipe->pipe_pair = pp;

	/*
	 * Mark both endpoints as present; they will later get free'd
	 * one at a time.  When both are free'd, then the whole pair
	 * is released.
	 */
	rpipe->pipe_present = PIPE_ACTIVE;
	wpipe->pipe_present = PIPE_ACTIVE;

	/*
	 * Eventually, the MAC Framework may initialize the label
	 * in ctor or init, but for now we do it elswhere to avoid
	 * blocking in ctor or init.
	 */
	pp->pp_label = NULL;

	return (0);
}