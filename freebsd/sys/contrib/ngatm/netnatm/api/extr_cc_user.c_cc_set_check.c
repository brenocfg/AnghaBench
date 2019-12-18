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
struct ccuser {int state; int /*<<< orphan*/  connq; } ;
struct ccconn {int dummy; } ;

/* Variables and functions */
 struct ccconn* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
#define  USER_IN_ARRIVED 129 
#define  USER_OUT_PREPARING 128 

__attribute__((used)) static struct ccconn *
cc_set_check(struct ccuser *user)
{
	switch(user->state) {

	  case USER_OUT_PREPARING:
	  case USER_IN_ARRIVED:
		return (TAILQ_FIRST(&user->connq));

	  default:
		return (NULL);
	}
}