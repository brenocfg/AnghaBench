#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct icl_conn {int /*<<< orphan*/  (* ic_error ) (struct icl_conn*) ;TYPE_1__* ic_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  so_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDOOFUS ; 
 int /*<<< orphan*/  stub1 (struct icl_conn*) ; 

__attribute__((used)) static void
icl_conn_fail(struct icl_conn *ic)
{
	if (ic->ic_socket == NULL)
		return;

	/*
	 * XXX
	 */
	ic->ic_socket->so_error = EDOOFUS;
	(ic->ic_error)(ic);
}