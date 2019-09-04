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
struct commit {int dummy; } ;

/* Variables and functions */
 char* get_commit_buffer (struct commit const*,unsigned long*) ; 
 int /*<<< orphan*/  gpg_sig_header ; 
 size_t gpg_sig_header_len ; 
 char* memchr (char const*,char,int) ; 
 scalar_t__ starts_with (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit const*,char const*) ; 

int parse_signed_commit(const struct commit *commit,
			struct strbuf *payload, struct strbuf *signature)
{

	unsigned long size;
	const char *buffer = get_commit_buffer(commit, &size);
	int in_signature, saw_signature = -1;
	const char *line, *tail;

	line = buffer;
	tail = buffer + size;
	in_signature = 0;
	saw_signature = 0;
	while (line < tail) {
		const char *sig = NULL;
		const char *next = memchr(line, '\n', tail - line);

		next = next ? next + 1 : tail;
		if (in_signature && line[0] == ' ')
			sig = line + 1;
		else if (starts_with(line, gpg_sig_header) &&
			 line[gpg_sig_header_len] == ' ')
			sig = line + gpg_sig_header_len + 1;
		if (sig) {
			strbuf_add(signature, sig, next - sig);
			saw_signature = 1;
			in_signature = 1;
		} else {
			if (*line == '\n')
				/* dump the whole remainder of the buffer */
				next = tail;
			strbuf_add(payload, line, next - line);
			in_signature = 0;
		}
		line = next;
	}
	unuse_commit_buffer(commit, buffer);
	return saw_signature;
}