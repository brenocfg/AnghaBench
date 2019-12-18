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
struct mac_biba_element {int mbe_type; int /*<<< orphan*/  mbe_grade; int /*<<< orphan*/  mbe_compartments; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_BIBA_BIT_TEST (int,int /*<<< orphan*/ ) ; 
 int MAC_BIBA_MAX_COMPARTMENTS ; 
#define  MAC_BIBA_TYPE_EQUAL 131 
#define  MAC_BIBA_TYPE_GRADE 130 
#define  MAC_BIBA_TYPE_HIGH 129 
#define  MAC_BIBA_TYPE_LOW 128 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
biba_dominate_element(struct mac_biba_element *a, struct mac_biba_element *b)
{
	int bit;

	switch (a->mbe_type) {
	case MAC_BIBA_TYPE_EQUAL:
	case MAC_BIBA_TYPE_HIGH:
		return (1);

	case MAC_BIBA_TYPE_LOW:
		switch (b->mbe_type) {
		case MAC_BIBA_TYPE_GRADE:
		case MAC_BIBA_TYPE_HIGH:
			return (0);

		case MAC_BIBA_TYPE_EQUAL:
		case MAC_BIBA_TYPE_LOW:
			return (1);

		default:
			panic("biba_dominate_element: b->mbe_type invalid");
		}

	case MAC_BIBA_TYPE_GRADE:
		switch (b->mbe_type) {
		case MAC_BIBA_TYPE_EQUAL:
		case MAC_BIBA_TYPE_LOW:
			return (1);

		case MAC_BIBA_TYPE_HIGH:
			return (0);

		case MAC_BIBA_TYPE_GRADE:
			for (bit = 1; bit <= MAC_BIBA_MAX_COMPARTMENTS; bit++)
				if (!MAC_BIBA_BIT_TEST(bit,
				    a->mbe_compartments) &&
				    MAC_BIBA_BIT_TEST(bit, b->mbe_compartments))
					return (0);
			return (a->mbe_grade >= b->mbe_grade);

		default:
			panic("biba_dominate_element: b->mbe_type invalid");
		}

	default:
		panic("biba_dominate_element: a->mbe_type invalid");
	}

	return (0);
}