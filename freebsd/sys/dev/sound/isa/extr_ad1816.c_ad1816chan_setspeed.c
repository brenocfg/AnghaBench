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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ad1816_info {int dummy; } ;
struct ad1816_chinfo {scalar_t__ dir; struct ad1816_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  RANGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ad1816_lock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_unlock (struct ad1816_info*) ; 
 int /*<<< orphan*/  ad1816_write (struct ad1816_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
ad1816chan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct ad1816_chinfo *ch = data;
    	struct ad1816_info *ad1816 = ch->parent;

    	RANGE(speed, 4000, 55200);
	ad1816_lock(ad1816);
    	ad1816_write(ad1816, (ch->dir == PCMDIR_PLAY)? 2 : 3, speed);
	ad1816_unlock(ad1816);
    	return speed;
}