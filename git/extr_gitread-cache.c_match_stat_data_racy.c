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
struct stat_data {int dummy; } ;
struct stat {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int MTIME_CHANGED ; 
 scalar_t__ is_racy_stat (struct index_state const*,struct stat_data const*) ; 
 int match_stat_data (struct stat_data const*,struct stat*) ; 

int match_stat_data_racy(const struct index_state *istate,
			 const struct stat_data *sd, struct stat *st)
{
	if (is_racy_stat(istate, sd))
		return MTIME_CHANGED;
	return match_stat_data(sd, st);
}