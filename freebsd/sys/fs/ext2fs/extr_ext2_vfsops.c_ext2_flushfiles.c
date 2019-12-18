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
struct thread {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int vflush (struct mount*,int /*<<< orphan*/ ,int,struct thread*) ; 

__attribute__((used)) static int
ext2_flushfiles(struct mount *mp, int flags, struct thread *td)
{
	int error;

	error = vflush(mp, 0, flags, td);
	return (error);
}