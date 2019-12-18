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
struct adf_accel_dev {int dummy; } ;
typedef  enum adf_event { ____Placeholder_adf_event } adf_event ;

/* Variables and functions */
#define  ADF_EVENT_INIT 133 
#define  ADF_EVENT_RESTARTED 132 
#define  ADF_EVENT_RESTARTING 131 
#define  ADF_EVENT_SHUTDOWN 130 
#define  ADF_EVENT_START 129 
#define  ADF_EVENT_STOP 128 
 int qat_crypto_init (struct adf_accel_dev*) ; 
 int qat_crypto_shutdown (struct adf_accel_dev*) ; 

__attribute__((used)) static int qat_crypto_event_handler(struct adf_accel_dev *accel_dev,
				    enum adf_event event)
{
	int ret;

	switch (event) {
	case ADF_EVENT_INIT:
		ret = qat_crypto_init(accel_dev);
		break;
	case ADF_EVENT_SHUTDOWN:
		ret = qat_crypto_shutdown(accel_dev);
		break;
	case ADF_EVENT_RESTARTING:
	case ADF_EVENT_RESTARTED:
	case ADF_EVENT_START:
	case ADF_EVENT_STOP:
	default:
		ret = 0;
	}
	return ret;
}