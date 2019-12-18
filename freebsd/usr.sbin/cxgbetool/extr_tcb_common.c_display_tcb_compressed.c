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
typedef  int /*<<< orphan*/  _TCBVAR ;

/* Variables and functions */
 int g_tN ; 
 int /*<<< orphan*/  t4_display_tcb_aux_0 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t4_display_tcb_aux_1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t4_display_tcb_aux_2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t4_display_tcb_aux_3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t5_display_tcb_aux_0 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t5_display_tcb_aux_1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t5_display_tcb_aux_2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t5_display_tcb_aux_3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t6_display_tcb_aux_0 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t6_display_tcb_aux_1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t6_display_tcb_aux_2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t6_display_tcb_aux_3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t6_display_tcb_aux_4 (int /*<<< orphan*/ *,int) ; 

void
display_tcb_compressed(_TCBVAR *tvp,int aux)
{

  if (g_tN==4) {
    t4_display_tcb_aux_0(tvp,aux);
    if      (1==aux) t4_display_tcb_aux_1(tvp,aux);
    else if (2==aux) t4_display_tcb_aux_2(tvp,aux);
    else if (3==aux) t4_display_tcb_aux_3(tvp,aux);

  } else if (g_tN==5) {
    t5_display_tcb_aux_0(tvp,aux);
    if      (1==aux) t5_display_tcb_aux_1(tvp,aux);
    else if (2==aux) t5_display_tcb_aux_2(tvp,aux);
    else if (3==aux) t5_display_tcb_aux_3(tvp,aux);
  } else if (g_tN==6) {
    t6_display_tcb_aux_0(tvp,aux);
    if      (1==aux) t6_display_tcb_aux_1(tvp,aux);
    else if (2==aux) t6_display_tcb_aux_2(tvp,aux);
    else if (3==aux) t6_display_tcb_aux_3(tvp,aux);
    else if (4==aux) t6_display_tcb_aux_4(tvp,aux); 
  }
}