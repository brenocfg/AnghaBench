#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_LowQmPortal; } ;
typedef  TYPE_3__ t_QmPortal ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  e_DpaaSwPortal ;
struct TYPE_4__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_5__ {TYPE_1__ config; } ;

/* Variables and functions */

__attribute__((used)) static e_DpaaSwPortal QmPortalGetSwPortalId(t_Handle h_QmPortal)
{
    t_QmPortal *p_QmPortal = (t_QmPortal *)h_QmPortal;

    return (e_DpaaSwPortal)p_QmPortal->p_LowQmPortal->config.cpu;
}