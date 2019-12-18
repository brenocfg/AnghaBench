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
struct ucred {struct label* cr_label; } ;
struct socket {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  MAGIC_SOCKET ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  socket_check_receive ; 

__attribute__((used)) static int
test_socket_check_receive(struct ucred *cred, struct socket *so,
    struct label *solabel)
{

	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	SOCK_LOCK(so);
	LABEL_CHECK(solabel, MAGIC_SOCKET);
	SOCK_UNLOCK(so);
	COUNTER_INC(socket_check_receive);

	return (0);
}