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
struct switch_attr {int type; char* name; char* description; struct switch_attr* next; } ;

/* Variables and functions */
#define  SWITCH_TYPE_INT 131 
#define  SWITCH_TYPE_NOVAL 130 
#define  SWITCH_TYPE_PORTS 129 
#define  SWITCH_TYPE_STRING 128 
 int /*<<< orphan*/  printf (char*,int,char const*,char*,char*) ; 

__attribute__((used)) static void
print_attrs(const struct switch_attr *attr)
{
	int i = 0;
	while (attr) {
		const char *type;
		switch(attr->type) {
			case SWITCH_TYPE_INT:
				type = "int";
				break;
			case SWITCH_TYPE_STRING:
				type = "string";
				break;
			case SWITCH_TYPE_PORTS:
				type = "ports";
				break;
			case SWITCH_TYPE_NOVAL:
				type = "none";
				break;
			default:
				type = "unknown";
				break;
		}
		printf("\tAttribute %d (%s): %s (%s)\n", ++i, type, attr->name, attr->description);
		attr = attr->next;
	}
}