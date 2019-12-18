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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  netEnvId; } ;
typedef  TYPE_1__ t_FmPort ;

/* Variables and functions */

uint8_t FmPortGetNetEnvId(t_Handle h_FmPort)
{
    return ((t_FmPort*)h_FmPort)->netEnvId;
}