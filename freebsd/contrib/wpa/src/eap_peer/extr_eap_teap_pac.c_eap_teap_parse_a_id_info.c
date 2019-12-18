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
struct eap_teap_pac {int /*<<< orphan*/  a_id_info; int /*<<< orphan*/  a_id_info_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_teap_parse_hex (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * eap_teap_parse_a_id_info(struct eap_teap_pac *pac,
					     char *pos)
{
	os_free(pac->a_id_info);
	pac->a_id_info = eap_teap_parse_hex(pos, &pac->a_id_info_len);
	if (!pac->a_id_info)
		return "Invalid A-ID-Info";
	return NULL;
}