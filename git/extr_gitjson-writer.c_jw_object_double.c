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
struct json_writer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_double (struct json_writer*,int,double) ; 
 int /*<<< orphan*/  object_common (struct json_writer*,char const*) ; 

void jw_object_double(struct json_writer *jw, const char *key, int precision,
		      double value)
{
	object_common(jw, key);
	fmt_double(jw, precision, value);
}