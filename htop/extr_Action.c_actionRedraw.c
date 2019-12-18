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
typedef  int Htop_Reaction ;

/* Variables and functions */
 int HTOP_REDRAW_BAR ; 
 int HTOP_REFRESH ; 
 int /*<<< orphan*/  clear () ; 

__attribute__((used)) static Htop_Reaction actionRedraw() {
   clear();
   return HTOP_REFRESH | HTOP_REDRAW_BAR;
}