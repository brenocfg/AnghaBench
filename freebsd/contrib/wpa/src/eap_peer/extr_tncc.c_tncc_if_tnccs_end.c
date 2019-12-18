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

/* Variables and functions */
 int /*<<< orphan*/  IF_TNCCS_END ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ) ; 

char * tncc_if_tnccs_end(void)
{
	char *buf = os_malloc(100);
	if (buf == NULL)
		return NULL;
	os_snprintf(buf, 100, IF_TNCCS_END);
	return buf;
}