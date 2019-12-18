#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  data_type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ kstat_named_t ;

/* Variables and functions */
 int /*<<< orphan*/  kstat_set_string (int /*<<< orphan*/ ,char const*) ; 

void
kstat_named_init(kstat_named_t *knp, const char *name, uchar_t data_type)
{

	kstat_set_string(knp->name, name);
	knp->data_type = data_type;
}