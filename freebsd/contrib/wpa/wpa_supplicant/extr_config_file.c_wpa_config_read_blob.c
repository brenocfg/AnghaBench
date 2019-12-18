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
struct wpa_config_blob {int /*<<< orphan*/ * data; int /*<<< orphan*/ * name; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/ * base64_decode (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,char*,size_t) ; 
 unsigned char* os_realloc (unsigned char*,size_t) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 size_t os_strlen (char*) ; 
 struct wpa_config_blob* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_config_free_blob (struct wpa_config_blob*) ; 
 scalar_t__ wpa_config_get_line (char*,int,int /*<<< orphan*/ *,int*,char**) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static struct wpa_config_blob * wpa_config_read_blob(FILE *f, int *line,
						     const char *name)
{
	struct wpa_config_blob *blob;
	char buf[256], *pos;
	unsigned char *encoded = NULL, *nencoded;
	int end = 0;
	size_t encoded_len = 0, len;

	wpa_printf(MSG_MSGDUMP, "Line: %d - start of a new named blob '%s'",
		   *line, name);

	while (wpa_config_get_line(buf, sizeof(buf), f, line, &pos)) {
		if (os_strcmp(pos, "}") == 0) {
			end = 1;
			break;
		}

		len = os_strlen(pos);
		nencoded = os_realloc(encoded, encoded_len + len);
		if (nencoded == NULL) {
			wpa_printf(MSG_ERROR, "Line %d: not enough memory for "
				   "blob", *line);
			os_free(encoded);
			return NULL;
		}
		encoded = nencoded;
		os_memcpy(encoded + encoded_len, pos, len);
		encoded_len += len;
	}

	if (!end || !encoded) {
		wpa_printf(MSG_ERROR, "Line %d: blob was not terminated "
			   "properly", *line);
		os_free(encoded);
		return NULL;
	}

	blob = os_zalloc(sizeof(*blob));
	if (blob == NULL) {
		os_free(encoded);
		return NULL;
	}
	blob->name = os_strdup(name);
	blob->data = base64_decode(encoded, encoded_len, &blob->len);
	os_free(encoded);

	if (blob->name == NULL || blob->data == NULL) {
		wpa_config_free_blob(blob);
		return NULL;
	}

	return blob;
}