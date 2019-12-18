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
struct termp {size_t (* width ) (struct termp const*,char) ;} ;

/* Variables and functions */
 size_t stub1 (struct termp const*,char) ; 

size_t
term_len(const struct termp *p, size_t sz)
{

	return (*p->width)(p, ' ') * sz;
}