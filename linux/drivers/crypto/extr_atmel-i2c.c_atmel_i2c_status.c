#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct device {int dummy; } ;
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  error_text; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ STATUS_NOERR ; 
 scalar_t__ STATUS_SIZE ; 
 scalar_t__ STATUS_WAKE_SUCCESSFUL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* error_list ; 

__attribute__((used)) static int atmel_i2c_status(struct device *dev, u8 *status)
{
	size_t err_list_len = ARRAY_SIZE(error_list);
	int i;
	u8 err_id = status[1];

	if (*status != STATUS_SIZE)
		return 0;

	if (err_id == STATUS_WAKE_SUCCESSFUL || err_id == STATUS_NOERR)
		return 0;

	for (i = 0; i < err_list_len; i++)
		if (error_list[i].value == err_id)
			break;

	/* if err_id is not in the error_list then ignore it */
	if (i != err_list_len) {
		dev_err(dev, "%02x: %s:\n", err_id, error_list[i].error_text);
		return err_id;
	}

	return 0;
}