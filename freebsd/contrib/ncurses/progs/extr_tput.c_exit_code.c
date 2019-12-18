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
#define  BOOLEAN 130 
#define  NUMBER 129 
#define  STRING 128 

__attribute__((used)) static int
exit_code(int token, int value)
{
    int result = 99;

    switch (token) {
    case BOOLEAN:
	result = !value;	/* TRUE=0, FALSE=1 */
	break;
    case NUMBER:
	result = 0;		/* always zero */
	break;
    case STRING:
	result = value;		/* 0=normal, 1=missing */
	break;
    }
    return result;
}