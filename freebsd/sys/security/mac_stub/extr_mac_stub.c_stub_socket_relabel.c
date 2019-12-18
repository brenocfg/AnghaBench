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
struct ucred {int dummy; } ;
struct socket {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 

__attribute__((used)) static void
stub_socket_relabel(struct ucred *cred, struct socket *so,
    struct label *solabel, struct label *newlabel)
{

	SOCK_LOCK_ASSERT(so);
}