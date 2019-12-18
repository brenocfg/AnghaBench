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
struct termp {int dummy; } ;

/* Variables and functions */
 size_t term_len (struct termp const*,size_t) ; 

__attribute__((used)) static size_t
term_tbl_len(size_t sz, void *arg)
{
	return term_len((const struct termp *)arg, sz);
}