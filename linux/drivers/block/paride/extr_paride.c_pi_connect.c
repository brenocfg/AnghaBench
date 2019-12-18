#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* proto; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* connect ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  pi_claim (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void pi_connect(PIA * pi)
{
	pi_claim(pi);
	pi->proto->connect(pi);
}