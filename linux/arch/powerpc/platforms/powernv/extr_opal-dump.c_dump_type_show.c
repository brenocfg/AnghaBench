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
struct dump_obj {int type; } ;
struct dump_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* dump_type_to_string (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 

__attribute__((used)) static ssize_t dump_type_show(struct dump_obj *dump_obj,
			      struct dump_attribute *attr,
			      char *buf)
{

	return sprintf(buf, "0x%x %s\n", dump_obj->type,
		       dump_type_to_string(dump_obj->type));
}