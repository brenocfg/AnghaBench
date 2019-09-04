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
struct date_mode {int type; scalar_t__ local; } ;
typedef  enum date_mode_type { ____Placeholder_date_mode_type } date_mode_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int DATE_STRFTIME ; 

struct date_mode *date_mode_from_type(enum date_mode_type type)
{
	static struct date_mode mode;
	if (type == DATE_STRFTIME)
		BUG("cannot create anonymous strftime date_mode struct");
	mode.type = type;
	mode.local = 0;
	return &mode;
}