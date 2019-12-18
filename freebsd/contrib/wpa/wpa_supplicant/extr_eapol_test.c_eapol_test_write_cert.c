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
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned char* base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,unsigned char*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void eapol_test_write_cert(FILE *f, const char *subject,
				  const struct wpabuf *cert)
{
	unsigned char *encoded;

	encoded = base64_encode(wpabuf_head(cert), wpabuf_len(cert), NULL);
	if (encoded == NULL)
		return;
	fprintf(f, "%s\n-----BEGIN CERTIFICATE-----\n%s"
		"-----END CERTIFICATE-----\n\n", subject, encoded);
	os_free(encoded);
}