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
struct pax {int flags; int /*<<< orphan*/  pax_header; } ;
struct archive_string {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int WRITE_LIBARCHIVE_XATTR ; 
 int WRITE_SCHILY_XATTR ; 
 int /*<<< orphan*/  add_pax_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_pax_attr_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char const*) ; 
 int /*<<< orphan*/  archive_strcpy (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 char* base64_encode (char const*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
archive_write_pax_header_xattr(struct pax *pax, const char *encoded_name,
    const void *value, size_t value_len)
{
	struct archive_string s;
	char *encoded_value;

	if (pax->flags & WRITE_LIBARCHIVE_XATTR) {
		encoded_value = base64_encode((const char *)value, value_len);

		if (encoded_name != NULL && encoded_value != NULL) {
			archive_string_init(&s);
			archive_strcpy(&s, "LIBARCHIVE.xattr.");
			archive_strcat(&s, encoded_name);
			add_pax_attr(&(pax->pax_header), s.s, encoded_value);
			archive_string_free(&s);
		}
		free(encoded_value);
	}
	if (pax->flags & WRITE_SCHILY_XATTR) {
		archive_string_init(&s);
		archive_strcpy(&s, "SCHILY.xattr.");
		archive_strcat(&s, encoded_name);
		add_pax_attr_binary(&(pax->pax_header), s.s, value, value_len);
		archive_string_free(&s);
	}
}