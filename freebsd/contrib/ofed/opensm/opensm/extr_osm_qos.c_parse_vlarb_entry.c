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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {unsigned int vl; scalar_t__ weight; } ;
typedef  TYPE_1__ ib_vl_arb_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  parse_one_unsigned (char const*,char,unsigned int*) ; 

__attribute__((used)) static int parse_vlarb_entry(const char *str, ib_vl_arb_element_t * e)
{
	unsigned val;
	const char *p = str;
	p += parse_one_unsigned(p, ':', &val);
	e->vl = val % 15;
	p += parse_one_unsigned(p, ',', &val);
	e->weight = (uint8_t) val;
	return (int)(p - str);
}