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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  show_rev (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int show_abbrev(const struct object_id *oid, void *cb_data)
{
	show_rev(NORMAL, oid, NULL);
	return 0;
}