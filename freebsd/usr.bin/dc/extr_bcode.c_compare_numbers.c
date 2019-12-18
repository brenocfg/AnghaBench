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
typedef  scalar_t__ u_int ;
struct number {scalar_t__ scale; int /*<<< orphan*/  number; } ;
typedef  enum bcode_compare { ____Placeholder_bcode_compare } bcode_compare ;

/* Variables and functions */
#define  BCODE_EQUAL 133 
#define  BCODE_GREATER 132 
#define  BCODE_LESS 131 
#define  BCODE_NOT_EQUAL 130 
#define  BCODE_NOT_GREATER 129 
#define  BCODE_NOT_LESS 128 
 int BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_number (struct number*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  normalize (struct number*,scalar_t__) ; 

__attribute__((used)) static bool
compare_numbers(enum bcode_compare type, struct number *a, struct number *b)
{
	u_int scale;
	int cmp;

	scale = max(a->scale, b->scale);

	if (scale > a->scale)
		normalize(a, scale);
	else if (scale > b->scale)
		normalize(b, scale);

	cmp = BN_cmp(a->number, b->number);

	free_number(a);
	free_number(b);

	switch (type) {
	case BCODE_EQUAL:
		return (cmp == 0);
	case BCODE_NOT_EQUAL:
		return (cmp != 0);
	case BCODE_LESS:
		return (cmp < 0);
	case BCODE_NOT_LESS:
		return (cmp >= 0);
	case BCODE_GREATER:
		return (cmp > 0);
	case BCODE_NOT_GREATER:
		return (cmp <= 0);
	}
	return (false);
}