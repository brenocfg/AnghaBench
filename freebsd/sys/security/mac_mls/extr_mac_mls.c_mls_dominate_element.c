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
struct mac_mls_element {int mme_type; int /*<<< orphan*/  mme_level; int /*<<< orphan*/  mme_compartments; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_BIT_TEST (int,int /*<<< orphan*/ ) ; 
 int MAC_MLS_MAX_COMPARTMENTS ; 
#define  MAC_MLS_TYPE_EQUAL 131 
#define  MAC_MLS_TYPE_HIGH 130 
#define  MAC_MLS_TYPE_LEVEL 129 
#define  MAC_MLS_TYPE_LOW 128 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
mls_dominate_element(struct mac_mls_element *a, struct mac_mls_element *b)
{
	int bit;

	switch (a->mme_type) {
	case MAC_MLS_TYPE_EQUAL:
	case MAC_MLS_TYPE_HIGH:
		return (1);

	case MAC_MLS_TYPE_LOW:
		switch (b->mme_type) {
		case MAC_MLS_TYPE_LEVEL:
		case MAC_MLS_TYPE_HIGH:
			return (0);

		case MAC_MLS_TYPE_EQUAL:
		case MAC_MLS_TYPE_LOW:
			return (1);

		default:
			panic("mls_dominate_element: b->mme_type invalid");
		}

	case MAC_MLS_TYPE_LEVEL:
		switch (b->mme_type) {
		case MAC_MLS_TYPE_EQUAL:
		case MAC_MLS_TYPE_LOW:
			return (1);

		case MAC_MLS_TYPE_HIGH:
			return (0);

		case MAC_MLS_TYPE_LEVEL:
			for (bit = 1; bit <= MAC_MLS_MAX_COMPARTMENTS; bit++)
				if (!MAC_MLS_BIT_TEST(bit,
				    a->mme_compartments) &&
				    MAC_MLS_BIT_TEST(bit, b->mme_compartments))
					return (0);
			return (a->mme_level >= b->mme_level);

		default:
			panic("mls_dominate_element: b->mme_type invalid");
		}

	default:
		panic("mls_dominate_element: a->mme_type invalid");
	}

	return (0);
}