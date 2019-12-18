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
struct TYPE_2__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  model; } ;
struct device_match_result {TYPE_1__ ident_data; } ;
typedef  int /*<<< orphan*/  revision ;
typedef  int /*<<< orphan*/  product ;

/* Variables and functions */
 int /*<<< orphan*/  cam_strvis (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static int
print_dev_ata(struct device_match_result *dev_result, char *tmpstr)
{
	char product[48], revision[16];

	cam_strvis(product, dev_result->ident_data.model,
	    sizeof(dev_result->ident_data.model), sizeof(product));
	cam_strvis(revision, dev_result->ident_data.revision,
	    sizeof(dev_result->ident_data.revision), sizeof(revision));
	sprintf(tmpstr, "<%s %s>", product, revision);

	return (0);
}