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
typedef  char uint8_t ;
typedef  scalar_t__ term_char_t ;
struct TYPE_3__ {scalar_t__ unicode_base; scalar_t__ length; scalar_t__ cp437_base; } ;

/* Variables and functions */
 TYPE_1__* cp437table ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static uint8_t
vga_get_cp437(term_char_t c)
{
	int min, mid, max;

	min = 0;
	max = nitems(cp437table) - 1;

	if (c < cp437table[0].unicode_base ||
	    c > cp437table[max].unicode_base + cp437table[max].length)
		return '?';

	while (max >= min) {
		mid = (min + max) / 2;
		if (c < cp437table[mid].unicode_base)
			max = mid - 1;
		else if (c > cp437table[mid].unicode_base +
		    cp437table[mid].length)
			min = mid + 1;
		else
			return (c - cp437table[mid].unicode_base +
			    cp437table[mid].cp437_base);
	}

	return '?';
}