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
struct ref_filter {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ FILTER_REFS_BRANCHES ; 
 scalar_t__ FILTER_REFS_REMOTES ; 
 scalar_t__ FILTER_REFS_TAGS ; 
 int ref_kind_from_refname (char const*) ; 

__attribute__((used)) static int filter_ref_kind(struct ref_filter *filter, const char *refname)
{
	if (filter->kind == FILTER_REFS_BRANCHES ||
	    filter->kind == FILTER_REFS_REMOTES ||
	    filter->kind == FILTER_REFS_TAGS)
		return filter->kind;
	return ref_kind_from_refname(refname);
}