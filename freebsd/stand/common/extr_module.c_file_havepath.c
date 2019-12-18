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
struct TYPE_2__ {int /*<<< orphan*/  (* arch_getdev ) (int /*<<< orphan*/ *,char const*,char const**) ;} ;

/* Variables and functions */
 TYPE_1__ archsw ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,char const**) ; 

__attribute__((used)) static int
file_havepath(const char *name)
{
	const char		*cp;

	archsw.arch_getdev(NULL, name, &cp);
	return (cp != name || strchr(name, '/') != NULL);
}