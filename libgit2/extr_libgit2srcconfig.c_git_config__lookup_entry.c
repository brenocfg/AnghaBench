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
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GET_NO_ERRORS ; 
 int /*<<< orphan*/  GET_NO_MISSING ; 
 int get_entry (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ) ; 

int git_config__lookup_entry(
	git_config_entry **out,
	const git_config *cfg,
	const char *key,
	bool no_errors)
{
	return get_entry(
		out, cfg, key, false, no_errors ? GET_NO_ERRORS : GET_NO_MISSING);
}