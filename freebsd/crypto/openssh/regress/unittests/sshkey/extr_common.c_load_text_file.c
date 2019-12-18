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
typedef  char u_char ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sshbuf* load_file (char const*) ; 
 int /*<<< orphan*/  sshbuf_consume_end (struct sshbuf*,int) ; 
 int sshbuf_len (struct sshbuf*) ; 
 char* sshbuf_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 

struct sshbuf *
load_text_file(const char *name)
{
	struct sshbuf *ret = load_file(name);
	const u_char *p;

	/* Trim whitespace at EOL */
	for (p = sshbuf_ptr(ret); sshbuf_len(ret) > 0;) {
		if (p[sshbuf_len(ret) - 1] == '\r' ||
		    p[sshbuf_len(ret) - 1] == '\t' ||
		    p[sshbuf_len(ret) - 1] == ' ' ||
		    p[sshbuf_len(ret) - 1] == '\n')
			ASSERT_INT_EQ(sshbuf_consume_end(ret, 1), 0);
		else
			break;
	}
	/* \0 terminate */
	ASSERT_INT_EQ(sshbuf_put_u8(ret, 0), 0);
	return ret;
}