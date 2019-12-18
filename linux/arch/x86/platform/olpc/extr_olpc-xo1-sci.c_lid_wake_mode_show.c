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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t lid_wake_mode ; 
 char** lid_wake_mode_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t lid_wake_mode_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	const char *mode = lid_wake_mode_names[lid_wake_mode];
	return sprintf(buf, "%s\n", mode);
}