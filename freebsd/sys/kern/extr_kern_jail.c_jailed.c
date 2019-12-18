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
struct ucred {int /*<<< orphan*/ * cr_prison; } ;

/* Variables and functions */
 int /*<<< orphan*/  prison0 ; 

int
jailed(struct ucred *cred)
{

	return (cred->cr_prison != &prison0);
}