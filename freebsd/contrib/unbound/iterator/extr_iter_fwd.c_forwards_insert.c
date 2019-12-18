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
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_forwards {int dummy; } ;
struct delegpt {int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int forwards_insert_data (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct delegpt*) ; 

__attribute__((used)) static int
forwards_insert(struct iter_forwards* fwd, uint16_t c, struct delegpt* dp)
{
	return forwards_insert_data(fwd, c, dp->name, dp->namelen,
		dp->namelabs, dp);
}