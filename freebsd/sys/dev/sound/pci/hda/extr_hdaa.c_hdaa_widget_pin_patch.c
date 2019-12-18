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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/ * HDA_COLORS ; 
 int HDA_CONFIG_DEFAULTCONF_ASSOCIATION_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_ASSOCIATION_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_COLOR_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_COLOR_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_DEVICE_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_LOCATION_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_LOCATION_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_MISC_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_MISC_SHIFT ; 
 int HDA_CONFIG_DEFAULTCONF_SEQUENCE_MASK ; 
 int HDA_CONFIG_DEFAULTCONF_SEQUENCE_SHIFT ; 
 int /*<<< orphan*/ * HDA_CONNECTORS ; 
 int /*<<< orphan*/ * HDA_CONNS ; 
 int /*<<< orphan*/ * HDA_DEVS ; 
 int /*<<< orphan*/ * HDA_LOCS ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strsep (char**,char*) ; 
 int strtol (char*,char**,int) ; 

uint32_t
hdaa_widget_pin_patch(uint32_t config, const char *str)
{
	char buf[256];
	char *key, *value, *rest, *bad;
	int ival, i;

	strlcpy(buf, str, sizeof(buf));
	rest = buf;
	while ((key = strsep(&rest, "=")) != NULL) {
		value = strsep(&rest, " \t");
		if (value == NULL)
			break;
		ival = strtol(value, &bad, 10);
		if (strcmp(key, "seq") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_SEQUENCE_MASK;
			config |= ((ival << HDA_CONFIG_DEFAULTCONF_SEQUENCE_SHIFT) &
			    HDA_CONFIG_DEFAULTCONF_SEQUENCE_MASK);
		} else if (strcmp(key, "as") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_ASSOCIATION_MASK;
			config |= ((ival << HDA_CONFIG_DEFAULTCONF_ASSOCIATION_SHIFT) &
			    HDA_CONFIG_DEFAULTCONF_ASSOCIATION_MASK);
		} else if (strcmp(key, "misc") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_MISC_MASK;
			config |= ((ival << HDA_CONFIG_DEFAULTCONF_MISC_SHIFT) &
			    HDA_CONFIG_DEFAULTCONF_MISC_MASK);
		} else if (strcmp(key, "color") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_COLOR_MASK;
			if (bad[0] == 0) {
				config |= ((ival << HDA_CONFIG_DEFAULTCONF_COLOR_SHIFT) &
				    HDA_CONFIG_DEFAULTCONF_COLOR_MASK);
			}
			for (i = 0; i < 16; i++) {
				if (strcasecmp(HDA_COLORS[i], value) == 0) {
					config |= (i << HDA_CONFIG_DEFAULTCONF_COLOR_SHIFT);
					break;
				}
			}
		} else if (strcmp(key, "ctype") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE_MASK;
			if (bad[0] == 0) {
			config |= ((ival << HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE_SHIFT) &
			    HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE_MASK);
			}
			for (i = 0; i < 16; i++) {
				if (strcasecmp(HDA_CONNECTORS[i], value) == 0) {
					config |= (i << HDA_CONFIG_DEFAULTCONF_CONNECTION_TYPE_SHIFT);
					break;
				}
			}
		} else if (strcmp(key, "device") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_DEVICE_MASK;
			if (bad[0] == 0) {
				config |= ((ival << HDA_CONFIG_DEFAULTCONF_DEVICE_SHIFT) &
				    HDA_CONFIG_DEFAULTCONF_DEVICE_MASK);
				continue;
			}
			for (i = 0; i < 16; i++) {
				if (strcasecmp(HDA_DEVS[i], value) == 0) {
					config |= (i << HDA_CONFIG_DEFAULTCONF_DEVICE_SHIFT);
					break;
				}
			}
		} else if (strcmp(key, "loc") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_LOCATION_MASK;
			if (bad[0] == 0) {
				config |= ((ival << HDA_CONFIG_DEFAULTCONF_LOCATION_SHIFT) &
				    HDA_CONFIG_DEFAULTCONF_LOCATION_MASK);
				continue;
			}
			for (i = 0; i < 64; i++) {
				if (strcasecmp(HDA_LOCS[i], value) == 0) {
					config |= (i << HDA_CONFIG_DEFAULTCONF_LOCATION_SHIFT);
					break;
				}
			}
		} else if (strcmp(key, "conn") == 0) {
			config &= ~HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK;
			if (bad[0] == 0) {
				config |= ((ival << HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_SHIFT) &
				    HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_MASK);
				continue;
			}
			for (i = 0; i < 4; i++) {
				if (strcasecmp(HDA_CONNS[i], value) == 0) {
					config |= (i << HDA_CONFIG_DEFAULTCONF_CONNECTIVITY_SHIFT);
					break;
				}
			}
		}
	}
	return (config);
}