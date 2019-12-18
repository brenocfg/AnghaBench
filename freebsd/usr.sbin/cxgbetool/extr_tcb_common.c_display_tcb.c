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
 scalar_t__ PRNTSTYL_COMP ; 
 scalar_t__ PRNTSTYL_LIST ; 
 scalar_t__ PRNTSTYL_RAW ; 
 scalar_t__ PRNTSTYL_VERBOSE ; 
 int /*<<< orphan*/  display_list_tcb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  display_tcb_compressed (int /*<<< orphan*/ *,int) ; 
 scalar_t__ g_prntstyl ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tcb_hexdump (int /*<<< orphan*/ ,unsigned char*,int) ; 

void
display_tcb(_TCBVAR *tvp,unsigned char *buf,int aux)
{
  if (g_prntstyl==PRNTSTYL_VERBOSE ||
      g_prntstyl==PRNTSTYL_RAW) {
    tcb_hexdump(0,buf,128); 
    printf("\n"); 
  }

  if (g_prntstyl==PRNTSTYL_VERBOSE ||
      g_prntstyl==PRNTSTYL_LIST) {
    display_list_tcb(tvp,aux);
  }

  if (g_prntstyl==PRNTSTYL_VERBOSE ||
      g_prntstyl==PRNTSTYL_COMP) {
    display_tcb_compressed(tvp,aux);
  }
  
}