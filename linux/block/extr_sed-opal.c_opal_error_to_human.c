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

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 char const** opal_errors ; 

__attribute__((used)) static const char *opal_error_to_human(int error)
{
	if (error == 0x3f)
		return "Failed";

	if (error >= ARRAY_SIZE(opal_errors) || error < 0)
		return "Unknown Error";

	return opal_errors[error];
}