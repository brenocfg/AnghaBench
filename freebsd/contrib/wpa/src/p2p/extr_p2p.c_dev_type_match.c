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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ WPA_GET_BE32 (int /*<<< orphan*/  const*) ; 
 int WPS_DEV_TYPE_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int dev_type_match(const u8 *dev_type, const u8 *req_dev_type)
{
	if (os_memcmp(dev_type, req_dev_type, WPS_DEV_TYPE_LEN) == 0)
		return 1;
	if (os_memcmp(dev_type, req_dev_type, 2) == 0 &&
	    WPA_GET_BE32(&req_dev_type[2]) == 0 &&
	    WPA_GET_BE16(&req_dev_type[6]) == 0)
		return 1; /* Category match with wildcard OUI/sub-category */
	return 0;
}