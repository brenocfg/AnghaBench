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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sotorawcb (struct socket*) ; 

__attribute__((used)) static int
raw_upeeraddr(struct socket *so, struct sockaddr **nam)
{

	KASSERT(sotorawcb(so) != NULL, ("raw_upeeraddr: rp == NULL"));

	return (ENOTCONN);
}