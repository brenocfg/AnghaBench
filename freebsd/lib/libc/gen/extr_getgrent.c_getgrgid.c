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
union key {int /*<<< orphan*/  gid; } ;
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 struct group* getgr (int /*<<< orphan*/ ,union key) ; 
 int /*<<< orphan*/  wrap_getgrgid_r ; 

struct group *
getgrgid(gid_t gid)
{
	union key key;

	key.gid = gid;
	return (getgr(wrap_getgrgid_r, key));
}