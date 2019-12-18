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
typedef  char u8 ;
struct ieee802_11_elems {int mesh_id_len; int mesh_config_len; int supp_rates_len; int ext_supp_rates_len; int* supp_rates; int* ext_supp_rates; int /*<<< orphan*/ * mesh_config; int /*<<< orphan*/  mesh_id; } ;

/* Variables and functions */
 scalar_t__ ParseFailed ; 
 scalar_t__ ieee802_11_parse_elems (char const*,size_t,struct ieee802_11_elems*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

__attribute__((used)) static int mesh_attr_text(const u8 *ies, size_t ies_len, char *buf, char *end)
{
	struct ieee802_11_elems elems;
	char *mesh_id, *pos = buf;
	u8 *bss_basic_rate_set;
	int bss_basic_rate_set_len, ret, i;

	if (ieee802_11_parse_elems(ies, ies_len, &elems, 0) == ParseFailed)
		return -1;

	if (elems.mesh_id_len < 1)
		return 0;

	mesh_id = os_malloc(elems.mesh_id_len + 1);
	if (mesh_id == NULL)
		return -1;

	os_memcpy(mesh_id, elems.mesh_id, elems.mesh_id_len);
	mesh_id[elems.mesh_id_len] = '\0';
	ret = os_snprintf(pos, end - pos, "mesh_id=%s\n", mesh_id);
	os_free(mesh_id);
	if (os_snprintf_error(end - pos, ret))
		return pos - buf;
	pos += ret;

	if (elems.mesh_config_len > 6) {
		ret = os_snprintf(pos, end - pos,
				  "active_path_selection_protocol_id=0x%02x\n"
				  "active_path_selection_metric_id=0x%02x\n"
				  "congestion_control_mode_id=0x%02x\n"
				  "synchronization_method_id=0x%02x\n"
				  "authentication_protocol_id=0x%02x\n"
				  "mesh_formation_info=0x%02x\n"
				  "mesh_capability=0x%02x\n",
				  elems.mesh_config[0], elems.mesh_config[1],
				  elems.mesh_config[2], elems.mesh_config[3],
				  elems.mesh_config[4], elems.mesh_config[5],
				  elems.mesh_config[6]);
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	bss_basic_rate_set = os_malloc(elems.supp_rates_len +
		elems.ext_supp_rates_len);
	if (bss_basic_rate_set == NULL)
		return -1;

	bss_basic_rate_set_len = 0;
	for (i = 0; i < elems.supp_rates_len; i++) {
		if (elems.supp_rates[i] & 0x80) {
			bss_basic_rate_set[bss_basic_rate_set_len++] =
				(elems.supp_rates[i] & 0x7f) * 5;
		}
	}
	for (i = 0; i < elems.ext_supp_rates_len; i++) {
		if (elems.ext_supp_rates[i] & 0x80) {
			bss_basic_rate_set[bss_basic_rate_set_len++] =
				(elems.ext_supp_rates[i] & 0x7f) * 5;
		}
	}
	if (bss_basic_rate_set_len > 0) {
		ret = os_snprintf(pos, end - pos, "bss_basic_rate_set=%d",
				  bss_basic_rate_set[0]);
		if (os_snprintf_error(end - pos, ret))
			goto fail;
		pos += ret;

		for (i = 1; i < bss_basic_rate_set_len; i++) {
			ret = os_snprintf(pos, end - pos, " %d",
					  bss_basic_rate_set[i]);
			if (os_snprintf_error(end - pos, ret))
				goto fail;
			pos += ret;
		}

		ret = os_snprintf(pos, end - pos, "\n");
		if (os_snprintf_error(end - pos, ret))
			goto fail;
		pos += ret;
	}
fail:
	os_free(bss_basic_rate_set);

	return pos - buf;
}