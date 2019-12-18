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
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dumpdev ; 
 int /*<<< orphan*/  kern_getenv (char*) ; 

__attribute__((used)) static void
g_dev_init(struct g_class *mp)
{

	dumpdev = kern_getenv("dumpdev");
}