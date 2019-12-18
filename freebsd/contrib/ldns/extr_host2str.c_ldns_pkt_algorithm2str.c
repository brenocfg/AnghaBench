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
typedef  int /*<<< orphan*/  ldns_buffer ;
typedef  int /*<<< orphan*/  ldns_algorithm ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_algorithm2buffer_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ldns_buffer_export2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int) ; 

char *
ldns_pkt_algorithm2str(ldns_algorithm algorithm)
{
	char *str;
	ldns_buffer *buf;

	buf = ldns_buffer_new(10);
	if (!buf) {
		return NULL;
	}

	str = NULL;
	if (ldns_algorithm2buffer_str(buf, algorithm)
	    == LDNS_STATUS_OK) {
		str = ldns_buffer_export2str(buf);
	}

	ldns_buffer_free(buf);
	return str;
}