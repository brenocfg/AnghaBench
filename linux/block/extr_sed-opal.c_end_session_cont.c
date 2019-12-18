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
struct opal_dev {scalar_t__ tsn; scalar_t__ hsn; } ;

/* Variables and functions */
 int parse_and_check_status (struct opal_dev*) ; 

__attribute__((used)) static int end_session_cont(struct opal_dev *dev)
{
	dev->hsn = 0;
	dev->tsn = 0;

	return parse_and_check_status(dev);
}