#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* ref_name; char const* id_str; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 scalar_t__ git__strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *rebase_onto_name(const git_annotated_commit *onto)
{
	if (onto->ref_name && git__strncmp(onto->ref_name, "refs/heads/", 11) == 0)
		return onto->ref_name + 11;
	else if (onto->ref_name)
		return onto->ref_name;
	else
		return onto->id_str;
}