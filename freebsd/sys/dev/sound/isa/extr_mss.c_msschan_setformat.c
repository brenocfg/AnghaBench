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
struct mss_info {int dummy; } ;
struct mss_chinfo {struct mss_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  mss_format (struct mss_chinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 

__attribute__((used)) static int
msschan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct mss_chinfo *ch = data;
	struct mss_info *mss = ch->parent;

	mss_lock(mss);
	mss_format(ch, format);
	mss_unlock(mss);
	return 0;
}