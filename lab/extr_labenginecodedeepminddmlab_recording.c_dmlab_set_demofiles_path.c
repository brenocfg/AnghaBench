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
struct TYPE_3__ {int /*<<< orphan*/  demofiles_path; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ dmlabRecordingContext ;

/* Variables and functions */
 int /*<<< orphan*/  DMLAB_RECORDING_ERROR_NONE ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 

void dmlab_set_demofiles_path(dmlabRecordingContext* context,
                              const char* path) {
  context->error = DMLAB_RECORDING_ERROR_NONE;

  Q_strncpyz(context->demofiles_path, path, sizeof(context->demofiles_path));
}