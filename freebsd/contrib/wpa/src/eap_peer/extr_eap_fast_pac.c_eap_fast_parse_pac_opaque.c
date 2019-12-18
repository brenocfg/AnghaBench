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
struct eap_fast_pac {int /*<<< orphan*/ * pac_opaque; int /*<<< orphan*/  pac_opaque_len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * eap_fast_parse_hex (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char * eap_fast_parse_pac_opaque(struct eap_fast_pac *pac,
					      char *pos)
{
	os_free(pac->pac_opaque);
	pac->pac_opaque = eap_fast_parse_hex(pos, &pac->pac_opaque_len);
	if (pac->pac_opaque == NULL)
		return "Invalid PAC-Opaque";
	return NULL;
}