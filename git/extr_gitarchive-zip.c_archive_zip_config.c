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
 int userdiff_config (char const*,char const*) ; 

__attribute__((used)) static int archive_zip_config(const char *var, const char *value, void *data)
{
	return userdiff_config(var, value);
}