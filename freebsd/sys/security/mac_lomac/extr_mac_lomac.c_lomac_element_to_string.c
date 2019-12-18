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
struct mac_lomac_element {int mle_type; int /*<<< orphan*/  mle_grade; } ;

/* Variables and functions */
#define  MAC_LOMAC_TYPE_EQUAL 131 
#define  MAC_LOMAC_TYPE_GRADE 130 
#define  MAC_LOMAC_TYPE_HIGH 129 
#define  MAC_LOMAC_TYPE_LOW 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 int sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static int
lomac_element_to_string(struct sbuf *sb, struct mac_lomac_element *element)
{

	switch (element->mle_type) {
	case MAC_LOMAC_TYPE_HIGH:
		return (sbuf_printf(sb, "high"));

	case MAC_LOMAC_TYPE_LOW:
		return (sbuf_printf(sb, "low"));

	case MAC_LOMAC_TYPE_EQUAL:
		return (sbuf_printf(sb, "equal"));

	case MAC_LOMAC_TYPE_GRADE:
		return (sbuf_printf(sb, "%d", element->mle_grade));

	default:
		panic("lomac_element_to_string: invalid type (%d)",
		    element->mle_type);
	}
}