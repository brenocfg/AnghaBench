#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int untagged; int notempty; } ;
struct hostapd_vlan {int vlan_id; struct hostapd_vlan* next; int /*<<< orphan*/  bridge; int /*<<< orphan*/  ifname; TYPE_1__ vlan_desc; } ;
struct hostapd_bss_config {struct hostapd_vlan* vlan; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IFNAMSIZ ; 
 int MAX_VLAN_ID ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int VLAN_ID_WILDCARD ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ os_strlen (char*) ; 
 struct hostapd_vlan* os_zalloc (int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int hostapd_config_read_vlan_file(struct hostapd_bss_config *bss,
					 const char *fname)
{
	FILE *f;
	char buf[128], *pos, *pos2, *pos3;
	int line = 0, vlan_id;
	struct hostapd_vlan *vlan;

	f = fopen(fname, "r");
	if (!f) {
		wpa_printf(MSG_ERROR, "VLAN file '%s' not readable.", fname);
		return -1;
	}

	while (fgets(buf, sizeof(buf), f)) {
		line++;

		if (buf[0] == '#')
			continue;
		pos = buf;
		while (*pos != '\0') {
			if (*pos == '\n') {
				*pos = '\0';
				break;
			}
			pos++;
		}
		if (buf[0] == '\0')
			continue;

		if (buf[0] == '*') {
			vlan_id = VLAN_ID_WILDCARD;
			pos = buf + 1;
		} else {
			vlan_id = strtol(buf, &pos, 10);
			if (buf == pos || vlan_id < 1 ||
			    vlan_id > MAX_VLAN_ID) {
				wpa_printf(MSG_ERROR, "Invalid VLAN ID at "
					   "line %d in '%s'", line, fname);
				fclose(f);
				return -1;
			}
		}

		while (*pos == ' ' || *pos == '\t')
			pos++;
		pos2 = pos;
		while (*pos2 != ' ' && *pos2 != '\t' && *pos2 != '\0')
			pos2++;

		if (*pos2 != '\0')
			*(pos2++) = '\0';

		if (*pos == '\0' || os_strlen(pos) > IFNAMSIZ) {
			wpa_printf(MSG_ERROR, "Invalid VLAN ifname at line %d "
				   "in '%s'", line, fname);
			fclose(f);
			return -1;
		}

		while (*pos2 == ' ' || *pos2 == '\t')
			pos2++;
		pos3 = pos2;
		while (*pos3 != ' ' && *pos3 != '\t' && *pos3 != '\0')
			pos3++;
		*pos3 = '\0';

		vlan = os_zalloc(sizeof(*vlan));
		if (vlan == NULL) {
			wpa_printf(MSG_ERROR, "Out of memory while reading "
				   "VLAN interfaces from '%s'", fname);
			fclose(f);
			return -1;
		}

		vlan->vlan_id = vlan_id;
		vlan->vlan_desc.untagged = vlan_id;
		vlan->vlan_desc.notempty = !!vlan_id;
		os_strlcpy(vlan->ifname, pos, sizeof(vlan->ifname));
		os_strlcpy(vlan->bridge, pos2, sizeof(vlan->bridge));
		vlan->next = bss->vlan;
		bss->vlan = vlan;
	}

	fclose(f);

	return 0;
}