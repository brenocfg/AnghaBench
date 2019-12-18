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
struct TYPE_3__ {char const ch; int value; struct TYPE_3__* child; struct TYPE_3__* sibling; } ;
typedef  TYPE_1__ TRIES ;

/* Variables and functions */
 int ERR ; 
 int OK ; 
 scalar_t__ UChar (char const) ; 

__attribute__((used)) static int
find_definition(TRIES * tree, const char *str)
{
    TRIES *ptr;
    int result = OK;

    if (str != 0 && *str != '\0') {
	for (ptr = tree; ptr != 0; ptr = ptr->sibling) {
	    if (UChar(*str) == UChar(ptr->ch)) {
		if (str[1] == '\0' && ptr->child != 0) {
		    result = ERR;
		} else if ((result = find_definition(ptr->child, str + 1))
			   == OK) {
		    result = ptr->value;
		} else if (str[1] == '\0') {
		    result = ERR;
		}
	    }
	    if (result != OK)
		break;
	}
    }
    return (result);
}