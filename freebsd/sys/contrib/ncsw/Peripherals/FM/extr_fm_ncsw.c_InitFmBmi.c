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
struct TYPE_3__ {int /*<<< orphan*/  p_FmDriverParam; int /*<<< orphan*/  p_FmBmiRegs; } ;
typedef  TYPE_1__ t_Fm ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  fman_bmi_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error InitFmBmi(t_Fm *p_Fm)
{
    return (t_Error)fman_bmi_init(p_Fm->p_FmBmiRegs, p_Fm->p_FmDriverParam);
}