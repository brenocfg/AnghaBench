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
struct socket {int dummy; } ;

/* Variables and functions */
 int SU_ISCONNECTED ; 
 int SU_OK ; 
 int /*<<< orphan*/  soreadable (struct socket*) ; 

__attribute__((used)) static int
sohasdata(struct socket *so, void *arg, int waitflag)
{

	if (!soreadable(so))
		return (SU_OK);

	return (SU_ISCONNECTED);
}