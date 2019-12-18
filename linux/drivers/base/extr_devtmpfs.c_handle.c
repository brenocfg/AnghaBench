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
typedef  scalar_t__ umode_t ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int handle_create (char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int handle_remove (char const*,struct device*) ; 

__attribute__((used)) static int handle(const char *name, umode_t mode, kuid_t uid, kgid_t gid,
		  struct device *dev)
{
	if (mode)
		return handle_create(name, mode, uid, gid, dev);
	else
		return handle_remove(name, dev);
}