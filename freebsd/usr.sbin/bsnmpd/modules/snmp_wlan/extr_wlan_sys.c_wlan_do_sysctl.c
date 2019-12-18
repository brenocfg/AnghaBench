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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  sval ;
struct wlan_config {int mesh_retryto; int mesh_holdingto; int mesh_confirmto; int mesh_maxretries; int hwmp_targetonly; int hwmp_replyforward; int hwmp_pathlifetime; int hwmp_roottimeout; int hwmp_rootint; int hwmp_rannint; int hwmp_inact; } ;
typedef  int /*<<< orphan*/  mib_name ;
typedef  int int32_t ;
typedef  enum wlan_syscl { ____Placeholder_wlan_syscl } wlan_syscl ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
#define  WLAN_HWMP_INACTIVITY_TO 138 
#define  WLAN_HWMP_PATH_LIFETIME 137 
#define  WLAN_HWMP_RANN_INT 136 
#define  WLAN_HWMP_REPLY_FORWARD 135 
#define  WLAN_HWMP_ROOT_INT 134 
#define  WLAN_HWMP_ROOT_TO 133 
#define  WLAN_HWMP_TARGET_ONLY 132 
#define  WLAN_MESH_CONFIRM_TO 131 
#define  WLAN_MESH_HOLDING_TO 130 
#define  WLAN_MESH_MAX_RETRIES 129 
#define  WLAN_MESH_RETRY_TO 128 
 int WLAN_SYSCTL_MAX ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int*,size_t) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wlan_sysctl ; 
 int /*<<< orphan*/  wlan_sysctl_name ; 

int32_t
wlan_do_sysctl(struct wlan_config *cfg, enum wlan_syscl which, int set)
{
	char mib_name[100];
	int val, sval;
	size_t len, vlen;

	if (set) {
		vlen = sizeof(sval);
		switch (which) {
		case WLAN_MESH_RETRY_TO:
			sval = cfg->mesh_retryto;
			break;
		case WLAN_MESH_HOLDING_TO:
			sval = cfg->mesh_holdingto;
			break;
		case WLAN_MESH_CONFIRM_TO:
			sval = cfg->mesh_confirmto;
			break;
		case WLAN_MESH_MAX_RETRIES:
			sval = cfg->mesh_maxretries;
			break;
		case WLAN_HWMP_TARGET_ONLY:
			sval = cfg->hwmp_targetonly;
			break;
		case WLAN_HWMP_REPLY_FORWARD:
			sval = cfg->hwmp_replyforward;
			break;
		case WLAN_HWMP_PATH_LIFETIME:
			sval = cfg->hwmp_pathlifetime;
			break;
		case WLAN_HWMP_ROOT_TO:
			sval = cfg->hwmp_roottimeout;
			break;
		case WLAN_HWMP_ROOT_INT:
			sval = cfg->hwmp_rootint;
			break;
		case WLAN_HWMP_RANN_INT:
			sval = cfg->hwmp_rannint;
			break;
		case WLAN_HWMP_INACTIVITY_TO:
			sval = cfg->hwmp_inact;
			break;
		default:
			return (-1);
		}
	} else {
		if (which >= WLAN_SYSCTL_MAX)
			return (-1);
		vlen = 0;
	}

	strlcpy(mib_name, wlan_sysctl_name, sizeof(mib_name));
	strlcat(mib_name, wlan_sysctl[which], sizeof(mib_name));
	len = sizeof (val);

	if (sysctlbyname(mib_name, &val, &len, (set? &sval : NULL), vlen) < 0) {
		syslog(LOG_ERR, "sysctl(%s) failed - %s", mib_name,
		    strerror(errno));
		return (-1);
	}

	switch (which) {
	case WLAN_MESH_RETRY_TO:
		cfg->mesh_retryto = val;
		break;
	case WLAN_MESH_HOLDING_TO:
		cfg->mesh_holdingto = val;
		break;
	case WLAN_MESH_CONFIRM_TO:
		cfg->mesh_confirmto = val;
		break;
	case WLAN_MESH_MAX_RETRIES:
		cfg->mesh_maxretries = val;
		break;
	case WLAN_HWMP_TARGET_ONLY:
		cfg->hwmp_targetonly = val;
		break;
	case WLAN_HWMP_REPLY_FORWARD:
		cfg->hwmp_replyforward = val;
		break;
	case WLAN_HWMP_PATH_LIFETIME:
		cfg->hwmp_pathlifetime = val;
		break;
	case WLAN_HWMP_ROOT_TO:
		cfg->hwmp_roottimeout = val;
		break;
	case WLAN_HWMP_ROOT_INT:
		cfg->hwmp_rootint = val;
		break;
	case WLAN_HWMP_RANN_INT:
		cfg->hwmp_rannint = val;
		break;
	case WLAN_HWMP_INACTIVITY_TO:
		cfg->hwmp_inact = val;
		break;
	default:
		/* NOTREACHED */
		abort();
	}

	return (0);
}