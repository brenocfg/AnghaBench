#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t directive_count; int /*<<< orphan*/ * directive; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTIVE_BACKWARD ; 
 int /*<<< orphan*/  DIRECTIVE_FORWARD ; 
 int /*<<< orphan*/  DIRECTIVE_POSITION ; 
 int /*<<< orphan*/  DIRECTIVE_UNDEF ; 
 int /*<<< orphan*/  INTERR ; 
#define  T_BACKWARD 130 
#define  T_FORWARD 129 
#define  T_POSITION 128 
 TYPE_1__ collinfo ; 

void
add_order_bit(int kw)
{
	uint8_t bit = DIRECTIVE_UNDEF;

	switch (kw) {
	case T_FORWARD:
		bit = DIRECTIVE_FORWARD;
		break;
	case T_BACKWARD:
		bit = DIRECTIVE_BACKWARD;
		break;
	case T_POSITION:
		bit = DIRECTIVE_POSITION;
		break;
	default:
		INTERR;
		break;
	}
	collinfo.directive[collinfo.directive_count] |= bit;
}