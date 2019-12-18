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
struct sigev_node {scalar_t__ sn_id; int /*<<< orphan*/  sn_value; int /*<<< orphan*/  (* sn_func ) (int /*<<< orphan*/ ,struct aiocb*) ;} ;
struct aiocb {int dummy; } ;
typedef  int /*<<< orphan*/  (* aio_func ) (int /*<<< orphan*/ ,struct aiocb*) ;

/* Variables and functions */

__attribute__((used)) static void
aio_dispatch(struct sigev_node *sn)
{
	aio_func f = sn->sn_func;

	f(sn->sn_value, (struct aiocb *)sn->sn_id);
}