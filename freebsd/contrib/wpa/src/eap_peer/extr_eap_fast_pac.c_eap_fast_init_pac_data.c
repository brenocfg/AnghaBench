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
struct wpa_config_blob {int len; scalar_t__ data; } ;
struct eap_sm {int dummy; } ;
struct eap_fast_read_ctx {int buf_len; char* pos; char* end; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * f; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpa_config_blob* eap_get_config_blob (struct eap_sm*,char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memset (struct eap_fast_read_ctx*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int eap_fast_init_pac_data(struct eap_sm *sm, const char *pac_file,
				  struct eap_fast_read_ctx *rc)
{
	os_memset(rc, 0, sizeof(*rc));

	rc->buf_len = 2048;
	rc->buf = os_malloc(rc->buf_len);
	if (rc->buf == NULL)
		return -1;

	if (os_strncmp(pac_file, "blob://", 7) == 0) {
		const struct wpa_config_blob *blob;
		blob = eap_get_config_blob(sm, pac_file + 7);
		if (blob == NULL) {
			wpa_printf(MSG_INFO, "EAP-FAST: No PAC blob '%s' - "
				   "assume no PAC entries have been "
				   "provisioned", pac_file + 7);
			os_free(rc->buf);
			return -1;
		}
		rc->pos = (char *) blob->data;
		rc->end = (char *) blob->data + blob->len;
	} else {
		rc->f = fopen(pac_file, "rb");
		if (rc->f == NULL) {
			wpa_printf(MSG_INFO, "EAP-FAST: No PAC file '%s' - "
				   "assume no PAC entries have been "
				   "provisioned", pac_file);
			os_free(rc->buf);
			return -1;
		}
	}

	return 0;
}