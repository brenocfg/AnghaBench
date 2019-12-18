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
struct remote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pushremote_for_branch ; 
 struct remote* remote_get_1 (char const*,int /*<<< orphan*/ ) ; 

struct remote *pushremote_get(const char *name)
{
	return remote_get_1(name, pushremote_for_branch);
}