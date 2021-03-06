#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ value; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int EQUALTO ; 
 int GREATERTHAN ; 
 int LESSTHAN ; 

__attribute__((used)) static int
valcmp(const void *v1, const void *v2)
{
    const nltype *p1 = (const nltype *)v1;
    const nltype *p2 = (const nltype *)v2;

    if ( p1 -> value < p2 -> value ) {
	return LESSTHAN;
    }
    if ( p1 -> value > p2 -> value ) {
	return GREATERTHAN;
    }
    return EQUALTO;
}