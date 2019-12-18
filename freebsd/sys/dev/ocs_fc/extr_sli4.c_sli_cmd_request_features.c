#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_8__ {int /*<<< orphan*/  dword; } ;
typedef  TYPE_3__ sli4_features_t ;
struct TYPE_7__ {int /*<<< orphan*/  dword; } ;
struct TYPE_6__ {int /*<<< orphan*/  command; } ;
struct TYPE_9__ {TYPE_2__ command; int /*<<< orphan*/  qry; TYPE_1__ hdr; } ;
typedef  TYPE_4__ sli4_cmd_request_features_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_REQUEST_FEATURES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int32_t
sli_cmd_request_features(sli4_t *sli4, void *buf, size_t size, sli4_features_t mask, uint8_t query)
{
	sli4_cmd_request_features_t *features = buf;

	ocs_memset(buf, 0, size);

	features->hdr.command = SLI4_MBOX_COMMAND_REQUEST_FEATURES;

	if (query) {
		features->qry = TRUE;
	}
	features->command.dword = mask.dword;

	return sizeof(sli4_cmd_request_features_t);
}