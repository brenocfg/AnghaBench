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
struct port_state {char* name; } ;
struct led_classdev {struct port_state* trigger_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct port_state*) ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 struct port_state* port_states ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t led_port_state_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct port_state *state = led_cdev->trigger_data;
	int len = 0;
	int i;

	*buf = '\0';
	for (i = 0; i < ARRAY_SIZE(port_states); i++) {
		if (&port_states[i] == state)
			len += sprintf(buf+len, "[%s] ", port_states[i].name);
		else
			len += sprintf(buf+len, "%s ", port_states[i].name);
	}
	len += sprintf(buf+len, "\n");

	return len;
}