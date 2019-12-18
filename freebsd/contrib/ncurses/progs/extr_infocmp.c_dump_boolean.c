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
#define  ABSENT_BOOLEAN 131 
#define  CANCELLED_BOOLEAN 130 
#define  FALSE 129 
#define  TRUE 128 
 char const* s_absent ; 
 char const* s_cancel ; 

__attribute__((used)) static const char *
dump_boolean(int val)
/* display the value of a boolean capability */
{
    switch (val) {
    case ABSENT_BOOLEAN:
	return (s_absent);
    case CANCELLED_BOOLEAN:
	return (s_cancel);
    case FALSE:
	return ("F");
    case TRUE:
	return ("T");
    default:
	return ("?");
    }
}