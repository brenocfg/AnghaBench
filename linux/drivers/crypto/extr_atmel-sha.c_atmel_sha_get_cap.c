#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int has_dma; int has_dualbuff; int has_sha224; int has_sha_384_512; int has_uihv; int has_hmac; } ;
struct atmel_sha_dev {int hw_version; int /*<<< orphan*/  dev; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void atmel_sha_get_cap(struct atmel_sha_dev *dd)
{

	dd->caps.has_dma = 0;
	dd->caps.has_dualbuff = 0;
	dd->caps.has_sha224 = 0;
	dd->caps.has_sha_384_512 = 0;
	dd->caps.has_uihv = 0;
	dd->caps.has_hmac = 0;

	/* keep only major version number */
	switch (dd->hw_version & 0xff0) {
	case 0x510:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		dd->caps.has_sha_384_512 = 1;
		dd->caps.has_uihv = 1;
		dd->caps.has_hmac = 1;
		break;
	case 0x420:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		dd->caps.has_sha_384_512 = 1;
		dd->caps.has_uihv = 1;
		break;
	case 0x410:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		dd->caps.has_sha_384_512 = 1;
		break;
	case 0x400:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		break;
	case 0x320:
		break;
	default:
		dev_warn(dd->dev,
				"Unmanaged sha version, set minimum capabilities\n");
		break;
	}
}