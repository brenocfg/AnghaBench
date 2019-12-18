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
typedef  scalar_t__ u32 ;
struct opal_dev {scalar_t__ tsn; scalar_t__ hsn; int /*<<< orphan*/  parsed; } ;

/* Variables and functions */
 int EPERM ; 
 int parse_and_check_status (struct opal_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ response_get_u64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int start_opal_session_cont(struct opal_dev *dev)
{
	u32 hsn, tsn;
	int error = 0;

	error = parse_and_check_status(dev);
	if (error)
		return error;

	hsn = response_get_u64(&dev->parsed, 4);
	tsn = response_get_u64(&dev->parsed, 5);

	if (hsn == 0 && tsn == 0) {
		pr_debug("Couldn't authenticate session\n");
		return -EPERM;
	}

	dev->hsn = hsn;
	dev->tsn = tsn;

	return 0;
}