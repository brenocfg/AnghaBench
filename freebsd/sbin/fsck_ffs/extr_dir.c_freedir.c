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
typedef  union dinode {int dummy; } dinode ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  di_nlink ; 
 int /*<<< orphan*/  freeino (scalar_t__) ; 
 union dinode* ginode (scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 

__attribute__((used)) static void
freedir(ino_t ino, ino_t parent)
{
	union dinode *dp;

	if (ino != parent) {
		dp = ginode(parent);
		DIP_SET(dp, di_nlink, DIP(dp, di_nlink) - 1);
		inodirty(dp);
	}
	freeino(ino);
}