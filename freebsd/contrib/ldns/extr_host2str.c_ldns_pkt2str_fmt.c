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
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_output_format ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_OK ; 
 char* ldns_buffer_export2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_pkt2buffer_str_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

char *
ldns_pkt2str_fmt(const ldns_output_format *fmt, const ldns_pkt *pkt)
{
	char *result = NULL;
	ldns_buffer *tmp_buffer = ldns_buffer_new(LDNS_MAX_PACKETLEN);

	if (!tmp_buffer) {
		return NULL;
	}
	if (ldns_pkt2buffer_str_fmt(tmp_buffer, fmt, pkt)
		       	== LDNS_STATUS_OK) {
		/* export and return string, destroy rest */
		result = ldns_buffer_export2str(tmp_buffer);
	}

	ldns_buffer_free(tmp_buffer);
	return result;
}