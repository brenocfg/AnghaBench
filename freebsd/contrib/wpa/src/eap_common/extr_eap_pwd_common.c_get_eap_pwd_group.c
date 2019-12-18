#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  group_num; int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ EAP_PWD_group ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  crypto_ec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dragonfly_suitable_group (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 TYPE_1__* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

EAP_PWD_group * get_eap_pwd_group(u16 num)
{
	EAP_PWD_group *grp;

	if (!dragonfly_suitable_group(num, 1)) {
		wpa_printf(MSG_INFO, "EAP-pwd: unsuitable group %u", num);
		return NULL;
	}
	grp = os_zalloc(sizeof(EAP_PWD_group));
	if (!grp)
		return NULL;
	grp->group = crypto_ec_init(num);
	if (!grp->group) {
		wpa_printf(MSG_INFO, "EAP-pwd: unable to create EC group");
		os_free(grp);
		return NULL;
	}

	grp->group_num = num;
	wpa_printf(MSG_INFO, "EAP-pwd: provisioned group %d", num);

	return grp;
}