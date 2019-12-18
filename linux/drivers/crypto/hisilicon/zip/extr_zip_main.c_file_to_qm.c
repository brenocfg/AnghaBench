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
struct hisi_qm {int dummy; } ;
struct hisi_zip {struct hisi_qm qm; } ;
struct ctrl_debug_file {TYPE_1__* ctrl; } ;
struct TYPE_2__ {struct hisi_zip* hisi_zip; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hisi_qm *file_to_qm(struct ctrl_debug_file *file)
{
	struct hisi_zip *hisi_zip = file->ctrl->hisi_zip;

	return &hisi_zip->qm;
}