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
struct eap_teap_read_ctx {char* buf; int /*<<< orphan*/  line; } ;
struct eap_teap_pac {int dummy; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  eap_teap_deinit_pac_data (struct eap_teap_read_ctx*) ; 
 int /*<<< orphan*/  eap_teap_free_pac (struct eap_teap_pac*) ; 
 scalar_t__ eap_teap_init_pac_data (struct eap_sm*,char const*,struct eap_teap_read_ctx*) ; 
 char* eap_teap_parse_a_id (struct eap_teap_pac*,char*) ; 
 char* eap_teap_parse_a_id_info (struct eap_teap_pac*,char*) ; 
 char* eap_teap_parse_end (struct eap_teap_pac**,struct eap_teap_pac**) ; 
 char* eap_teap_parse_i_id (struct eap_teap_pac*,char*) ; 
 char* eap_teap_parse_pac_key (struct eap_teap_pac*,char*) ; 
 char* eap_teap_parse_pac_opaque (struct eap_teap_pac*,char*) ; 
 char* eap_teap_parse_pac_type (struct eap_teap_pac*,char*) ; 
 char* eap_teap_parse_start (struct eap_teap_pac**) ; 
 scalar_t__ eap_teap_read_line (struct eap_teap_read_ctx*,char**) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 char* pac_file_hdr ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int eap_teap_load_pac(struct eap_sm *sm, struct eap_teap_pac **pac_root,
		      const char *pac_file)
{
	struct eap_teap_read_ctx rc;
	struct eap_teap_pac *pac = NULL;
	int count = 0;
	char *pos;
	const char *err = NULL;

	if (!pac_file)
		return -1;

	if (eap_teap_init_pac_data(sm, pac_file, &rc) < 0)
		return 0;

	if (eap_teap_read_line(&rc, &pos) < 0) {
		/* empty file - assume it is fine to overwrite */
		eap_teap_deinit_pac_data(&rc);
		return 0;
	}
	if (os_strcmp(pac_file_hdr, rc.buf) != 0)
		err = "Unrecognized header line";

	while (!err && eap_teap_read_line(&rc, &pos) == 0) {
		if (os_strcmp(rc.buf, "START") == 0)
			err = eap_teap_parse_start(&pac);
		else if (os_strcmp(rc.buf, "END") == 0) {
			err = eap_teap_parse_end(pac_root, &pac);
			count++;
		} else if (!pac)
			err = "Unexpected line outside START/END block";
		else if (os_strcmp(rc.buf, "PAC-Type") == 0)
			err = eap_teap_parse_pac_type(pac, pos);
		else if (os_strcmp(rc.buf, "PAC-Key") == 0)
			err = eap_teap_parse_pac_key(pac, pos);
		else if (os_strcmp(rc.buf, "PAC-Opaque") == 0)
			err = eap_teap_parse_pac_opaque(pac, pos);
		else if (os_strcmp(rc.buf, "A-ID") == 0)
			err = eap_teap_parse_a_id(pac, pos);
		else if (os_strcmp(rc.buf, "I-ID") == 0)
			err = eap_teap_parse_i_id(pac, pos);
		else if (os_strcmp(rc.buf, "A-ID-Info") == 0)
			err = eap_teap_parse_a_id_info(pac, pos);
	}

	if (pac) {
		if (!err)
			err = "PAC block not terminated with END";
		eap_teap_free_pac(pac);
	}

	eap_teap_deinit_pac_data(&rc);

	if (err) {
		wpa_printf(MSG_INFO, "EAP-TEAP: %s in '%s:%d'",
			   err, pac_file, rc.line);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Read %d PAC entries from '%s'",
		   count, pac_file);

	return 0;
}