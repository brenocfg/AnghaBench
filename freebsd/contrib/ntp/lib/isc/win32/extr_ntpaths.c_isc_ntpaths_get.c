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
 int /*<<< orphan*/  Initialized ; 
#define  LOCAL_STATE_DIR 137 
#define  LWRESD_PID_PATH 136 
#define  LWRES_CONF_PATH 135 
#define  NAMED_CONF_PATH 134 
#define  NAMED_PID_PATH 133 
#define  RESOLV_CONF_PATH 132 
#define  RNDC_CONF_PATH 131 
#define  RNDC_KEY_PATH 130 
#define  SESSION_KEY_PATH 129 
#define  SYS_CONF_DIR 128 
 int /*<<< orphan*/  isc_ntpaths_init () ; 
 char* local_state_dir ; 
 char* lwresd_confFile ; 
 char* lwresd_defaultpidfile ; 
 char* lwresd_resolvconfFile ; 
 char* ns_confFile ; 
 char* ns_defaultpidfile ; 
 char* rndc_confFile ; 
 char* rndc_keyFile ; 
 char* session_keyFile ; 
 char* sys_conf_dir ; 

char *
isc_ntpaths_get(int ind) {
	if (!Initialized)
		isc_ntpaths_init();

	switch (ind) {
	case NAMED_CONF_PATH:
		return (ns_confFile);
		break;
	case LWRES_CONF_PATH:
		return (lwresd_confFile);
		break;
	case RESOLV_CONF_PATH:
		return (lwresd_resolvconfFile);
		break;
	case RNDC_CONF_PATH:
		return (rndc_confFile);
		break;
	case NAMED_PID_PATH:
		return (ns_defaultpidfile);
		break;
	case LWRESD_PID_PATH:
		return (lwresd_defaultpidfile);
		break;
	case LOCAL_STATE_DIR:
		return (local_state_dir);
		break;
	case SYS_CONF_DIR:
		return (sys_conf_dir);
		break;
	case RNDC_KEY_PATH:
		return (rndc_keyFile);
		break;
	case SESSION_KEY_PATH:
		return (session_keyFile);
		break;
	default:
		return (NULL);
	}
}