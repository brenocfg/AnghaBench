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
struct untracked_cache_dir {int check_only; } ;
struct read_data {struct untracked_cache_dir** ucd; } ;

/* Variables and functions */

__attribute__((used)) static void set_check_only(size_t pos, void *cb)
{
	struct read_data *rd = cb;
	struct untracked_cache_dir *ud = rd->ucd[pos];
	ud->check_only = 1;
}