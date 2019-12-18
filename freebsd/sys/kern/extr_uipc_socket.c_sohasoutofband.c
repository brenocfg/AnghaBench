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
struct socket {int /*<<< orphan*/  so_rdsel; int /*<<< orphan*/ * so_sigio; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSOCK ; 
 int /*<<< orphan*/  SIGURG ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
sohasoutofband(struct socket *so)
{

	if (so->so_sigio != NULL)
		pgsigio(&so->so_sigio, SIGURG, 0);
	selwakeuppri(&so->so_rdsel, PSOCK);
}