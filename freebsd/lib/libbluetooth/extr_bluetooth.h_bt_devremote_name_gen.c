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
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HCI_MANDATORY_PAGE_SCAN_MODE ; 
 int /*<<< orphan*/  NG_HCI_SCAN_REP_MODE0 ; 
 char* bt_devremote_name (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline char *
bt_devremote_name_gen(char const *btooth_devname, const bdaddr_t *remote)
{
	return (bt_devremote_name(btooth_devname, remote, 0, 0x0000,
		NG_HCI_SCAN_REP_MODE0, NG_HCI_MANDATORY_PAGE_SCAN_MODE));
}