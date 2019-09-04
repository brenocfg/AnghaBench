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
typedef  scalar_t__ dialogType_t ;
typedef  int /*<<< orphan*/  dialogResult_t ;

/* Variables and functions */
 int /*<<< orphan*/  DR_NO ; 
 int /*<<< orphan*/  DR_OK ; 
 scalar_t__ DT_YES_NO ; 
 int /*<<< orphan*/  Sys_Print (char const*) ; 

dialogResult_t Sys_Dialog( dialogType_t type, const char *message, const char *title ) {
	Sys_Print( message );
	return type == DT_YES_NO ? DR_NO : DR_OK;
}