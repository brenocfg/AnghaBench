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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  LCI_REQ_SUBELEM_MAX_AGE ; 
 int /*<<< orphan*/  WPA_GET_LE16 (int const*) ; 
 int* get_ie (int const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 hostapd_parse_location_lci_req_age(const u8 *buf, size_t len)
{
	const u8 *subelem;

	/* Range Request element + Location Subject + Maximum Age subelement */
	if (len < 3 + 1 + 4)
		return 0;

	/* Subelements are arranged as IEs */
	subelem = get_ie(buf + 4, len - 4, LCI_REQ_SUBELEM_MAX_AGE);
	if (subelem && subelem[1] == 2)
		return WPA_GET_LE16(subelem + 2);

	return 0;
}