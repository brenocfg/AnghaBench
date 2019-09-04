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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_exists ; 
 int trailer_set_if_exists (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int option_parse_if_exists(const struct option *opt,
				  const char *arg, int unset)
{
	return trailer_set_if_exists(&if_exists, arg);
}