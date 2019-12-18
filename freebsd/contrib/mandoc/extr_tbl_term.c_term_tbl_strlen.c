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
 size_t term_strlen (struct termp const*,char const*) ; 

__attribute__((used)) static size_t
term_tbl_strlen(const char *p, void *arg)
{
	return term_strlen((const struct termp *)arg, p);
}