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
struct TYPE_3__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ State ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int HTOP_REFRESH ; 
 int HTOP_SAVE_SETTINGS ; 
 int /*<<< orphan*/  Settings_invertSortOrder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Htop_Reaction actionInvertSortOrder(State* st) {
   Settings_invertSortOrder(st->settings);
   return HTOP_REFRESH | HTOP_SAVE_SETTINGS;
}