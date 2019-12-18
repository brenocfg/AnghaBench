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
 int /*<<< orphan*/  display_tcb (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * g_tcb_info ; 
 int parse_tcb (int /*<<< orphan*/ *,unsigned char*) ; 

void
parse_n_display_tcb(unsigned char *buf)
{
  _TCBVAR *tvp=g_tcb_info;
  int aux;

  aux=parse_tcb(tvp,buf);
  display_tcb(tvp,buf,aux);
}