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
struct pipepair {int /*<<< orphan*/  pp_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct pipepair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_create ; 

void
mac_pipe_create(struct ucred *cred, struct pipepair *pp)
{

	MAC_POLICY_PERFORM_NOSLEEP(pipe_create, cred, pp, pp->pp_label);
}