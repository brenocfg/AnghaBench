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
 int /*<<< orphan*/  REVERSED ; 
 int /*<<< orphan*/  show_rev (int /*<<< orphan*/ ,struct object_id const*,char const*) ; 

__attribute__((used)) static int anti_reference(const char *refname, const struct object_id *oid, int flag, void *cb_data)
{
	show_rev(REVERSED, oid, refname);
	return 0;
}