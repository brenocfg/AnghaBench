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
struct pipe {int pipe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PIPE_LOCKFL ; 
 int pipespace_new (struct pipe*,int) ; 

__attribute__((used)) static int
pipespace(struct pipe *cpipe, int size)
{

	KASSERT(cpipe->pipe_state & PIPE_LOCKFL,
		("Unlocked pipe passed to pipespace"));
	return (pipespace_new(cpipe, size));
}