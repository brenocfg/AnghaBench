#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 

void parse_commit_or_die(struct commit *item)
{
	if (parse_commit(item))
		die("unable to parse commit %s",
		    item ? oid_to_hex(&item->object.oid) : "(null)");
}