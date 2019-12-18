#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_driver_capa {int enc; } ;
struct TYPE_3__ {int capa; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ciphers_group_mgmt ; 
 int os_snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

__attribute__((used)) static int ctrl_iface_get_capability_group_mgmt(int res, char *strict,
						struct wpa_driver_capa *capa,
						char *buf, size_t buflen)
{
	int ret;
	char *pos, *end;
	unsigned int i;

	pos = buf;
	end = pos + buflen;

	if (res < 0)
		return 0;

	for (i = 0; i < ARRAY_SIZE(ciphers_group_mgmt); i++) {
		if (capa->enc & ciphers_group_mgmt[i].capa) {
			ret = os_snprintf(pos, end - pos, "%s%s",
					  pos == buf ? "" : " ",
					  ciphers_group_mgmt[i].name);
			if (os_snprintf_error(end - pos, ret))
				return pos - buf;
			pos += ret;
		}
	}

	return pos - buf;
}