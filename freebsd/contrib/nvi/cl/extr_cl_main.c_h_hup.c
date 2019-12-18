#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  killersig; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_SIGHUP ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_CLP ; 
 int /*<<< orphan*/  SIGHUP ; 
 TYPE_1__* clp ; 

__attribute__((used)) static void
h_hup(int signo)
{
	GLOBAL_CLP;

	F_SET(clp, CL_SIGHUP);
	clp->killersig = SIGHUP;
}