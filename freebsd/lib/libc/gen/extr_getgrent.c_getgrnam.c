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
union key {char const* name; } ;
struct group {int dummy; } ;

/* Variables and functions */
 struct group* getgr (int /*<<< orphan*/ ,union key) ; 
 int /*<<< orphan*/  wrap_getgrnam_r ; 

struct group *
getgrnam(const char *name)
{
	union key key;

	key.name = name;
	return (getgr(wrap_getgrnam_r, key));
}