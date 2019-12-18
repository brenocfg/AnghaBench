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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t ESR_ELx_EC (int /*<<< orphan*/ ) ; 
 char const** esr_class_str ; 

const char *esr_get_class_string(u32 esr)
{
	return esr_class_str[ESR_ELx_EC(esr)];
}