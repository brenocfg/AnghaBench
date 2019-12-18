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
typedef  int /*<<< orphan*/  vendor ;
struct TYPE_2__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct device_match_result {TYPE_1__ inq_data; } ;
typedef  int /*<<< orphan*/  revision ;
typedef  int /*<<< orphan*/  product ;

/* Variables and functions */
 int /*<<< orphan*/  cam_strvis (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static int
print_dev_scsi(struct device_match_result *dev_result, char *tmpstr)
{
	char vendor[16], product[48], revision[16];

	cam_strvis(vendor, dev_result->inq_data.vendor,
	    sizeof(dev_result->inq_data.vendor), sizeof(vendor));
	cam_strvis(product, dev_result->inq_data.product,
	    sizeof(dev_result->inq_data.product), sizeof(product));
	cam_strvis(revision, dev_result->inq_data.revision,
	    sizeof(dev_result->inq_data.revision), sizeof(revision));
	sprintf(tmpstr, "<%s %s %s>", vendor, product, revision);

	return (0);
}