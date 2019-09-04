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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char* default_encoding ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,char*,char const*) ; 
 char* reencode_string_len (char const*,size_t,char const*,char*,size_t*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,size_t,size_t) ; 

__attribute__((used)) static int encode_to_worktree(const char *path, const char *src, size_t src_len,
			      struct strbuf *buf, const char *enc)
{
	char *dst;
	size_t dst_len;

	/*
	 * No encoding is specified or there is nothing to encode.
	 * Tell the caller that the content was not modified.
	 */
	if (!enc || (src && !src_len))
		return 0;

	dst = reencode_string_len(src, src_len, enc, default_encoding,
				  &dst_len);
	if (!dst) {
		error(_("failed to encode '%s' from %s to %s"),
		      path, default_encoding, enc);
		return 0;
	}

	strbuf_attach(buf, dst, dst_len, dst_len + 1);
	return 1;
}