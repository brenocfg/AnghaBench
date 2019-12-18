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
struct TYPE_2__ {double s; double u; double f; } ;
struct oidvalue {int type; TYPE_1__ value; } ;

/* Variables and functions */
#define  FLOAT 130 
#define  SIGNED 129 
#define  UNSIGNED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
oidvalue_get_float(const struct oidvalue *ov)
{

	switch (ov->type) {
	case SIGNED:
		return (ov->value.s);
	case UNSIGNED:
		return (ov->value.u);
	case FLOAT:
		return (ov->value.f);
	default:
		assert(0 && "Unknown value type");
	}
}