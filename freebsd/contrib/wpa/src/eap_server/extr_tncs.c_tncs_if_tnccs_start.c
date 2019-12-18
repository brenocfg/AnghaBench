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
struct tncs_data {int /*<<< orphan*/  last_batchid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_TNCCS_START ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char * tncs_if_tnccs_start(struct tncs_data *tncs)
{
	char *buf = os_malloc(1000);
	if (buf == NULL)
		return NULL;
	tncs->last_batchid++;
	os_snprintf(buf, 1000, IF_TNCCS_START, tncs->last_batchid);
	return buf;
}