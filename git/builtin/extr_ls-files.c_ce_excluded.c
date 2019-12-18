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
struct index_state {int dummy; } ;
struct dir_struct {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int ce_to_dtype (struct cache_entry const*) ; 
 int is_excluded (struct dir_struct*,struct index_state*,char const*,int*) ; 

__attribute__((used)) static int ce_excluded(struct dir_struct *dir, struct index_state *istate,
		       const char *fullname, const struct cache_entry *ce)
{
	int dtype = ce_to_dtype(ce);
	return is_excluded(dir, istate, fullname, &dtype);
}