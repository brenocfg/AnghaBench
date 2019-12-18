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
struct thread {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct thread* curthread ; 
 int priv_check_cred (int /*<<< orphan*/ ,int) ; 

int
priv_check(struct thread *td, int priv)
{

	KASSERT(td == curthread, ("priv_check: td != curthread"));

	return (priv_check_cred(td->td_ucred, priv));
}