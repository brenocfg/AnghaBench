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
bsd_to_linux_v4l2_standard(struct v4l2_standard *vstd, struct l_v4l2_standard *lvstd)
{
	lvstd->index = vstd->index;
	lvstd->id = vstd->id;
	CTASSERT(sizeof(vstd->name) == sizeof(lvstd->name));
	memcpy(lvstd->name, vstd->name, sizeof(lvstd->name));
	lvstd->frameperiod = vstd->frameperiod;
	lvstd->framelines = vstd->framelines;
	CTASSERT(sizeof(vstd->reserved) == sizeof(lvstd->reserved));
	memcpy(lvstd->reserved, vstd->reserved, sizeof(lvstd->reserved));
	return (0);
}