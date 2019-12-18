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
struct get_options {int dummy; } ;

/* Variables and functions */
 int getit (struct get_options*,char*,int,char**) ; 

int
get_entry(struct get_options *opt, int argc, char **argv)
{
    return getit(opt, "get", argc, argv);
}