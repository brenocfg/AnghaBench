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
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pru_close ) (struct socket*) ;} ;

/* Variables and functions */
 TYPE_1__ raw_usrreqs ; 
 int /*<<< orphan*/  stub1 (struct socket*) ; 

__attribute__((used)) static void
rts_close(struct socket *so)
{

	raw_usrreqs.pru_close(so);
}