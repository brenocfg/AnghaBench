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
struct v4l2_standard {int /*<<< orphan*/  reserved; int /*<<< orphan*/  framelines; int /*<<< orphan*/  frameperiod; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  index; } ;
struct l_v4l2_standard {int /*<<< orphan*/  reserved; int /*<<< orphan*/  framelines; int /*<<< orphan*/  frameperiod; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
linux_to_bsd_v4l2_standard(struct l_v4l2_standard *lvstd, struct v4l2_standard *vstd)
{
	vstd->index = lvstd->index;
	vstd->id = lvstd->id;
	CTASSERT(sizeof(vstd->name) == sizeof(lvstd->name));
	memcpy(vstd->name, lvstd->name, sizeof(vstd->name));
	vstd->frameperiod = lvstd->frameperiod;
	vstd->framelines = lvstd->framelines;
	CTASSERT(sizeof(vstd->reserved) == sizeof(lvstd->reserved));
	memcpy(vstd->reserved, lvstd->reserved, sizeof(vstd->reserved));
	return (0);
}