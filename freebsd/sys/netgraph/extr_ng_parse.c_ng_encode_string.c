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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_PARSE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 
 int strlen (char const*) ; 

char *
ng_encode_string(const char *raw, int slen)
{
	char *cbuf;
	int off = 0;
	int i;

	cbuf = malloc(strlen(raw) * 4 + 3, M_NETGRAPH_PARSE, M_NOWAIT);
	if (cbuf == NULL)
		return (NULL);
	cbuf[off++] = '"';
	for (i = 0; i < slen; i++, raw++) {
		switch (*raw) {
		case '\t':
			cbuf[off++] = '\\';
			cbuf[off++] = 't';
			break;
		case '\f':
			cbuf[off++] = '\\';
			cbuf[off++] = 'f';
			break;
		case '\n':
			cbuf[off++] = '\\';
			cbuf[off++] = 'n';
			break;
		case '\r':
			cbuf[off++] = '\\';
			cbuf[off++] = 'r';
			break;
		case '\v':
			cbuf[off++] = '\\';
			cbuf[off++] = 'v';
			break;
		case '"':
		case '\\':
			cbuf[off++] = '\\';
			cbuf[off++] = *raw;
			break;
		default:
			if (*raw < 0x20 || *raw > 0x7e) {
				off += sprintf(cbuf + off,
				    "\\x%02x", (u_char)*raw);
				break;
			}
			cbuf[off++] = *raw;
			break;
		}
	}
	cbuf[off++] = '"';
	cbuf[off] = '\0';
	return (cbuf);
}