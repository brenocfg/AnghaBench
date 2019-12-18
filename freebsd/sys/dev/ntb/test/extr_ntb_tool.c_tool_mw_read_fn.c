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
struct tool_mw {char size; } ;
struct sysctl_req {int dummy; } ;
struct sbuf {int s_error; } ;
typedef  char ssize_t ;

/* Variables and functions */
 char DEFAULT_MW_SIZE ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_for_sysctl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,struct sysctl_req*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
tool_mw_read_fn(struct sysctl_req *req, struct tool_mw *inmw, char *read_addr,
    int *cmd_op, ssize_t buf_off, ssize_t buf_size, char *type)
{
	ssize_t index, size;
	struct sbuf *sb;
	int i, loop, rc;
	char *tmp;

	/* The below check is made to ignore sysctl read call. */
	if (*cmd_op == 0)
		return (0);

	/* Proceeds only when command R/W is requested using sysctl. */
	index = buf_off;
	tmp = read_addr;
	tmp += index;
	loop = ((buf_size == 0) || (buf_size > DEFAULT_MW_SIZE)) ?
	    DEFAULT_MW_SIZE : buf_size;
	/*
	 * 256 bytes of extra buffer has been allocated to print details like
	 * summary, size, notes, i.e., excluding data part.
	 */
	size = loop + 256;
	sb = sbuf_new_for_sysctl(NULL, NULL, size, req);
	if (sb == NULL) {
		rc = sb->s_error;
		return (rc);
	}

	if (!strcmp(type, "mw"))
		sbuf_printf(sb, "\nConfigured MW size\t: %zu\n", inmw->size);
	else if (!strcmp(type, "peer_mw"))
		sbuf_printf(sb, "\nConfigured Peer MW size\t: %zu\n",
		    inmw->size);
	sbuf_printf(sb, "R/W size\t\t: %zi\nR/W Offset\t\t: %zi\n\nData\n----"
	    "->", buf_size, buf_off);

	/*
	 * Data will be read based on MW size provided by the user using nbytes,
	 * which is limited to 1024 bytes if user req bigger size to read, check
	 * above loop calculation which is limiting or setting the MW read size.
	 * Below for loop prints data where in each line contains 32 bytes data
	 * and after each 8 bytes of data we used four spaces which ensures one
	 * data block.
	 */
	for (i = 0 ; i < loop; i++) {
		if ((i % 32) == 0) {
			sbuf_printf(sb, "\n%08zx:", index);
			index += 32;
		}
		if ((i % 8) == 0)
			sbuf_printf(sb, "    ");
		sbuf_printf(sb, "%02hhx", *(tmp+i));
	}
	if (buf_size > DEFAULT_MW_SIZE)
		sbuf_printf(sb, "\n\nNOTE: Truncating read size %zi->1024 "
		    "bytes\n", buf_size);

	/* cmd_op is set to zero after completion of each R/W command. */
	*cmd_op -= 1;
	rc = sbuf_finish(sb);
	sbuf_delete(sb);

	return (rc);
}