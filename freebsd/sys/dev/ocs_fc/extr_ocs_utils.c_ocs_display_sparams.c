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
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int /*<<< orphan*/  label ;
typedef  int /*<<< orphan*/  fc_plogi_payload_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_DEBUG_ENABLE_SPARAM_DUMP ; 
 int /*<<< orphan*/  ocs_ddump_buffer (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ocs_dump32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void*,int) ; 
 int /*<<< orphan*/  ocs_snprintf (char*,int,char*,char const*,...) ; 

void
ocs_display_sparams(const char *prelabel, const char *reqlabel, int dest, void *textbuf, void *sparams)
{
	char label[64];

	if (sparams == NULL) {
		return;
	}

	switch(dest) {
	case 0:
		if (prelabel != NULL) {
			ocs_snprintf(label, sizeof(label), "[%s] sparam: %s", prelabel, reqlabel);
		} else {
			ocs_snprintf(label, sizeof(label), "sparam: %s", reqlabel);
		}

		ocs_dump32(OCS_DEBUG_ENABLE_SPARAM_DUMP, NULL, label, sparams, sizeof(fc_plogi_payload_t));
		break;
	case 1:
		ocs_ddump_buffer((ocs_textbuf_t*) textbuf, reqlabel, 0, sparams, sizeof(fc_plogi_payload_t));
		break;
	}
}