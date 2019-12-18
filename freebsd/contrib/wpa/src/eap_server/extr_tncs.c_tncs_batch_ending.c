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
struct tncs_data {int /*<<< orphan*/  connectionID; struct tnc_if_imv* imv; } ;
struct tnc_if_imv {unsigned long name; int /*<<< orphan*/  imvID; scalar_t__ (* BatchEnding ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct tnc_if_imv* next; } ;
typedef  scalar_t__ TNC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void tncs_batch_ending(struct tncs_data *tncs)
{
	struct tnc_if_imv *imv;
	TNC_Result res;

	for (imv = tncs->imv; imv; imv = imv->next) {
		if (imv->BatchEnding == NULL)
			continue;

		wpa_printf(MSG_DEBUG, "TNC: Call BatchEnding for IMV '%s'",
			   imv->name);
		res = imv->BatchEnding(imv->imvID, tncs->connectionID);
		wpa_printf(MSG_DEBUG, "TNC: BatchEnding: %lu",
			   (unsigned long) res);
	}
}