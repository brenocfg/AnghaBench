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
typedef  char wchar_t ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* archive_entry_acl_to_text (struct archive_entry*,int /*<<< orphan*/ *,int) ; 
 char* archive_entry_acl_to_text_w (struct archive_entry*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,char const*) ; 
 int /*<<< orphan*/  assertEqualWString (char*,char*) ; 
 char* convert_s_to_ws (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  wcslen (char*) ; 

__attribute__((used)) static void
compare_acl_text(struct archive_entry *ae, int flags, const char *s)
{
	char *text;
	wchar_t *wtext;
	wchar_t *ws;
	ssize_t slen;

	ws = convert_s_to_ws(s);

	text = archive_entry_acl_to_text(ae, &slen, flags);
	assertEqualString(text, s);
	if (text != NULL)
		assertEqualInt(strlen(text), slen);
	wtext = archive_entry_acl_to_text_w(ae, &slen, flags);
	assertEqualWString(wtext, ws);
	if (wtext != NULL) {
		assertEqualInt(wcslen(wtext), slen);
	}
	free(text);
	free(wtext);
	free(ws);
}