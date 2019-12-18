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
struct sirf_data {struct serdev_device* serdev; } ;
struct serdev_device {int dummy; } ;
struct gnss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 struct sirf_data* gnss_get_drvdata (struct gnss_device*) ; 
 int /*<<< orphan*/  serdev_device_wait_until_sent (struct serdev_device*,int /*<<< orphan*/ ) ; 
 int serdev_device_write (struct serdev_device*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sirf_write_raw(struct gnss_device *gdev, const unsigned char *buf,
				size_t count)
{
	struct sirf_data *data = gnss_get_drvdata(gdev);
	struct serdev_device *serdev = data->serdev;
	int ret;

	/* write is only buffered synchronously */
	ret = serdev_device_write(serdev, buf, count, MAX_SCHEDULE_TIMEOUT);
	if (ret < 0 || ret < count)
		return ret;

	/* FIXME: determine if interrupted? */
	serdev_device_wait_until_sent(serdev, 0);

	return count;
}