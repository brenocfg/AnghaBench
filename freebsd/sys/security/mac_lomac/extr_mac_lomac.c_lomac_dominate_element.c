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
struct mac_lomac_element {int mle_type; int /*<<< orphan*/  mle_grade; } ;

/* Variables and functions */
#define  MAC_LOMAC_TYPE_EQUAL 131 
#define  MAC_LOMAC_TYPE_GRADE 130 
#define  MAC_LOMAC_TYPE_HIGH 129 
#define  MAC_LOMAC_TYPE_LOW 128 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
lomac_dominate_element(struct mac_lomac_element *a,
    struct mac_lomac_element *b)
{

	switch (a->mle_type) {
	case MAC_LOMAC_TYPE_EQUAL:
	case MAC_LOMAC_TYPE_HIGH:
		return (1);

	case MAC_LOMAC_TYPE_LOW:
		switch (b->mle_type) {
		case MAC_LOMAC_TYPE_GRADE:
		case MAC_LOMAC_TYPE_HIGH:
			return (0);

		case MAC_LOMAC_TYPE_EQUAL:
		case MAC_LOMAC_TYPE_LOW:
			return (1);

		default:
			panic("lomac_dominate_element: b->mle_type invalid");
		}

	case MAC_LOMAC_TYPE_GRADE:
		switch (b->mle_type) {
		case MAC_LOMAC_TYPE_EQUAL:
		case MAC_LOMAC_TYPE_LOW:
			return (1);

		case MAC_LOMAC_TYPE_HIGH:
			return (0);

		case MAC_LOMAC_TYPE_GRADE:
			return (a->mle_grade >= b->mle_grade);

		default:
			panic("lomac_dominate_element: b->mle_type invalid");
		}

	default:
		panic("lomac_dominate_element: a->mle_type invalid");
	}
}