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

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_CHARMAP 135 
#define  T_COLLATE 134 
#define  T_CTYPE 133 
#define  T_MESSAGES 132 
#define  T_MONETARY 131 
#define  T_NUMERIC 130 
#define  T_TIME 129 
#define  T_WIDTH 128 
 int get_category () ; 

const char *
category_name(void)
{
	switch (get_category()) {
	case T_CHARMAP:
		return ("CHARMAP");
	case T_WIDTH:
		return ("WIDTH");
	case T_COLLATE:
		return ("LC_COLLATE");
	case T_CTYPE:
		return ("LC_CTYPE");
	case T_MESSAGES:
		return ("LC_MESSAGES");
	case T_MONETARY:
		return ("LC_MONETARY");
	case T_NUMERIC:
		return ("LC_NUMERIC");
	case T_TIME:
		return ("LC_TIME");
	default:
		INTERR;
		return (NULL);
	}
}