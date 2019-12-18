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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_STRCPY (char*,char const*) ; 
 scalar_t__ OSAL_STRLEN (char const*) ; 

__attribute__((used)) static u32 ecore_dump_str(char *dump_buf,
						  bool dump,
						  const char *str)
{
	if (dump)
		OSAL_STRCPY(dump_buf, str);

	return (u32)OSAL_STRLEN(str) + 1;
}