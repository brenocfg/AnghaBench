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
struct sbuf {int dummy; } ;
struct mac_mls_element {int mme_type; int mme_level; int /*<<< orphan*/  mme_compartments; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_BIT_TEST (int,int /*<<< orphan*/ ) ; 
 int MAC_MLS_MAX_COMPARTMENTS ; 
#define  MAC_MLS_TYPE_EQUAL 131 
#define  MAC_MLS_TYPE_HIGH 130 
#define  MAC_MLS_TYPE_LEVEL 129 
#define  MAC_MLS_TYPE_LOW 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 int sbuf_printf (struct sbuf*,char*,...) ; 
 int sbuf_putc (struct sbuf*,char) ; 

__attribute__((used)) static int
mls_element_to_string(struct sbuf *sb, struct mac_mls_element *element)
{
	int i, first;

	switch (element->mme_type) {
	case MAC_MLS_TYPE_HIGH:
		return (sbuf_printf(sb, "high"));

	case MAC_MLS_TYPE_LOW:
		return (sbuf_printf(sb, "low"));

	case MAC_MLS_TYPE_EQUAL:
		return (sbuf_printf(sb, "equal"));

	case MAC_MLS_TYPE_LEVEL:
		if (sbuf_printf(sb, "%d", element->mme_level) == -1)
			return (-1);

		first = 1;
		for (i = 1; i <= MAC_MLS_MAX_COMPARTMENTS; i++) {
			if (MAC_MLS_BIT_TEST(i, element->mme_compartments)) {
				if (first) {
					if (sbuf_putc(sb, ':') == -1)
						return (-1);
					if (sbuf_printf(sb, "%d", i) == -1)
						return (-1);
					first = 0;
				} else {
					if (sbuf_printf(sb, "+%d", i) == -1)
						return (-1);
				}
			}
		}
		return (0);

	default:
		panic("mls_element_to_string: invalid type (%d)",
		    element->mme_type);
	}
}