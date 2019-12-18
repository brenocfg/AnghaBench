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
struct tlvhdr {scalar_t__ tlv_type; scalar_t__ tlv_length; } ;
struct tlv_template {scalar_t__ tmpl_type; scalar_t__ tmpl_length; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
tlv_check(const void *p, size_t size, const struct tlvhdr *tlv,
    const struct tlv_template *tmpl, boolean_t check_type)
{
	while (/* CONSTCOND */ 1) {
		if ((const char *)tlv - (const char *)p + sizeof(*tlv) > size) {
			return (EINVAL);
		}
		if ((check_type && tlv->tlv_type != tmpl->tmpl_type) ||
		    tlv->tlv_length != tmpl->tmpl_length) {
			return (EINVAL);
		}
		if (tmpl->tmpl_type == 0) {
			break;
		}
		tlv = (const struct tlvhdr *)
		    ((const char *)tlv + tlv->tlv_length);
		tmpl++;
	}

	return (0);
}