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
struct pfioc_src_nodes {unsigned int psn_len; char* psn_buf; struct pf_src_node* psn_src_nodes; } ;
struct pf_src_node {int dummy; } ;
typedef  int /*<<< orphan*/  psn ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETSRCNODES ; 
 int PF_OPT_SHOWALL ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_src_nodes*) ; 
 int /*<<< orphan*/  memset (struct pfioc_src_nodes*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  print_src_node (struct pf_src_node*,int) ; 
 char* realloc (char*,unsigned int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_show_src_nodes(int dev, int opts)
{
	struct pfioc_src_nodes psn;
	struct pf_src_node *p;
	char *inbuf = NULL, *newinbuf = NULL;
	unsigned int len = 0;
	int i;

	memset(&psn, 0, sizeof(psn));
	for (;;) {
		psn.psn_len = len;
		if (len) {
			newinbuf = realloc(inbuf, len);
			if (newinbuf == NULL)
				err(1, "realloc");
			psn.psn_buf = inbuf = newinbuf;
		}
		if (ioctl(dev, DIOCGETSRCNODES, &psn) < 0) {
			warn("DIOCGETSRCNODES");
			free(inbuf);
			return (-1);
		}
		if (psn.psn_len + sizeof(struct pfioc_src_nodes) < len)
			break;
		if (len == 0 && psn.psn_len == 0)
			goto done;
		if (len == 0 && psn.psn_len != 0)
			len = psn.psn_len;
		if (psn.psn_len == 0)
			goto done;	/* no src_nodes */
		len *= 2;
	}
	p = psn.psn_src_nodes;
	if (psn.psn_len > 0 && (opts & PF_OPT_SHOWALL))
		pfctl_print_title("SOURCE TRACKING NODES:");
	for (i = 0; i < psn.psn_len; i += sizeof(*p)) {
		print_src_node(p, opts);
		p++;
	}
done:
	free(inbuf);
	return (0);
}