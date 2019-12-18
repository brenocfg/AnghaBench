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
struct json_writer {int /*<<< orphan*/  pretty; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_common (struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_begin (struct json_writer*,int /*<<< orphan*/ ) ; 

void jw_array_inline_begin_array(struct json_writer *jw)
{
	array_common(jw);

	jw_array_begin(jw, jw->pretty);
}