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
struct pfsync_state {int /*<<< orphan*/  ifname; } ;
struct pfioc_states {unsigned int ps_len; char* ps_buf; struct pfsync_state* ps_states; } ;
typedef  int /*<<< orphan*/  ps ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETSTATES ; 
 int PF_OPT_SHOWALL ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_states*) ; 
 int /*<<< orphan*/  memset (struct pfioc_states*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  print_state (struct pfsync_state*,int) ; 
 char* realloc (char*,unsigned int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_show_states(int dev, const char *iface, int opts)
{
	struct pfioc_states ps;
	struct pfsync_state *p;
	char *inbuf = NULL, *newinbuf = NULL;
	unsigned int len = 0;
	int i, dotitle = (opts & PF_OPT_SHOWALL);

	memset(&ps, 0, sizeof(ps));
	for (;;) {
		ps.ps_len = len;
		if (len) {
			newinbuf = realloc(inbuf, len);
			if (newinbuf == NULL)
				err(1, "realloc");
			ps.ps_buf = inbuf = newinbuf;
		}
		if (ioctl(dev, DIOCGETSTATES, &ps) < 0) {
			warn("DIOCGETSTATES");
			free(inbuf);
			return (-1);
		}
		if (ps.ps_len + sizeof(struct pfioc_states) < len)
			break;
		if (len == 0 && ps.ps_len == 0)
			goto done;
		if (len == 0 && ps.ps_len != 0)
			len = ps.ps_len;
		if (ps.ps_len == 0)
			goto done;	/* no states */
		len *= 2;
	}
	p = ps.ps_states;
	for (i = 0; i < ps.ps_len; i += sizeof(*p), p++) {
		if (iface != NULL && strcmp(p->ifname, iface))
			continue;
		if (dotitle) {
			pfctl_print_title("STATES:");
			dotitle = 0;
		}
		print_state(p, opts);
	}
done:
	free(inbuf);
	return (0);
}