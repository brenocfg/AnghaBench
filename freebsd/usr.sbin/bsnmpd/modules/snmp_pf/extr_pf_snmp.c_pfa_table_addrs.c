#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct pfr_table {int /*<<< orphan*/  pfrt_name; } ;
struct TYPE_4__ {scalar_t__ pfra_af; } ;
struct TYPE_3__ {int /*<<< orphan*/  pfrt_name; } ;
struct pfr_astats {int pfrio_size; int pfrio_esize; TYPE_2__ pfras_a; struct pfr_astats* pfrio_buffer; TYPE_1__ pfrio_table; } ;
struct pfioc_table {int pfrio_size; int pfrio_esize; TYPE_2__ pfras_a; struct pfioc_table* pfrio_buffer; TYPE_1__ pfrio_table; } ;
struct pfa_entry {int /*<<< orphan*/  pfas; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DIOCRGETASTATS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pfa_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct pfr_astats*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfr_astats*) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pfr_astats*,int) ; 
 int /*<<< orphan*/  memset (struct pfr_astats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfa_table ; 
 struct pfr_astats* reallocf (struct pfr_astats*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
pfa_table_addrs(u_int sidx, struct pfr_table *pt)
{
	struct pfioc_table io;
	struct pfr_astats *t = NULL;
	struct pfa_entry *e;
	int i, numaddrs = 1;

	if (pt == NULL)
		return (-1);

	memset(&io, 0, sizeof(io));
	strlcpy(io.pfrio_table.pfrt_name, pt->pfrt_name,
	    sizeof(io.pfrio_table.pfrt_name));

	for (;;) {
		t = reallocf(t, numaddrs * sizeof(struct pfr_astats));
		if (t == NULL) {
			syslog(LOG_ERR, "pfa_table_addrs(): reallocf(): %s",
			    strerror(errno));
			numaddrs = -1;
			goto error;
		}

		memset(t, 0, sizeof(*t));
		io.pfrio_size = numaddrs;
		io.pfrio_buffer = t;
		io.pfrio_esize = sizeof(struct pfr_astats);

		if (ioctl(dev, DIOCRGETASTATS, &io)) {
			syslog(LOG_ERR, "pfa_table_addrs(): ioctl() on %s: %s",
			    pt->pfrt_name, strerror(errno));
			numaddrs = -1;
			break;
		}

		if (numaddrs >= io.pfrio_size)
			break;

		numaddrs = io.pfrio_size;
	}

	for (i = 0; i < numaddrs; i++) {
		if ((t + i)->pfras_a.pfra_af != AF_INET &&
		    (t + i)->pfras_a.pfra_af != AF_INET6) {
			numaddrs = i;
			break;
		}

		e = (struct pfa_entry *)malloc(sizeof(struct pfa_entry));
		if (e == NULL) {
			syslog(LOG_ERR, "pfa_table_addrs(): malloc(): %s",
			    strerror(errno));
			numaddrs = -1;
			break;
		}
		e->index = sidx + i;
		memcpy(&e->pfas, t + i, sizeof(struct pfr_astats));
		TAILQ_INSERT_TAIL(&pfa_table, e, link);
	}

	free(t);
error:
	return (numaddrs);
}