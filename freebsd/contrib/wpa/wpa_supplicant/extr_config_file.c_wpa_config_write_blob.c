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
struct wpa_config_blob {char* name; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned char* base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,unsigned char*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 

__attribute__((used)) static int wpa_config_write_blob(FILE *f, struct wpa_config_blob *blob)
{
	unsigned char *encoded;

	encoded = base64_encode(blob->data, blob->len, NULL);
	if (encoded == NULL)
		return -1;

	fprintf(f, "\nblob-base64-%s={\n%s}\n", blob->name, encoded);
	os_free(encoded);
	return 0;
}