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
struct tnc_if_imv {int /*<<< orphan*/  supported_types; int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tncs_free_imv(struct tnc_if_imv *imv)
{
	os_free(imv->name);
	os_free(imv->path);
	os_free(imv->supported_types);
}