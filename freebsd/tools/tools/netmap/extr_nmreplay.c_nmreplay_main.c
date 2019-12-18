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
struct _qs {char* prod_ifname; int /*<<< orphan*/ * pcap; int /*<<< orphan*/  cons_ifname; int /*<<< orphan*/  t0; } ;
struct pipe_args {int /*<<< orphan*/ * pb; int /*<<< orphan*/  cons_core; struct _qs q; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEE (char*,...) ; 
 int /*<<< orphan*/  WWW (char*) ; 
 int /*<<< orphan*/  cons (void*) ; 
 int /*<<< orphan*/  destroy_pcap (int /*<<< orphan*/ *) ; 
 int do_abort ; 
 int /*<<< orphan*/ * nm_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_prod (void*) ; 
 int /*<<< orphan*/ * readpcap (char const*) ; 
 int /*<<< orphan*/  set_tns_now (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setaffinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *
nmreplay_main(void *_a)
{
    struct pipe_args *a = _a;
    struct _qs *q = &a->q;
    const char *cap_fname = q->prod_ifname;

    setaffinity(a->cons_core);
    set_tns_now(&q->t0, 0); /* starting reference */
    if (cap_fname == NULL) {
	goto fail;
    }
    q->pcap = readpcap(cap_fname);
    if (q->pcap == NULL) {
	EEE("unable to read file %s", cap_fname);
	goto fail;
    }
    pcap_prod((void*)a);
    destroy_pcap(q->pcap);
    q->pcap = NULL;
    a->pb = nm_open(q->cons_ifname, NULL, 0, NULL);
    if (a->pb == NULL) {
	EEE("cannot open netmap on %s", q->cons_ifname);
	do_abort = 1; // XXX any better way ?
	return NULL;
    }
    /* continue as cons() */
    WWW("prepare to send packets");
    usleep(1000);
    cons((void*)a);
    EEE("exiting on abort");
fail:
    if (q->pcap != NULL) {
	destroy_pcap(q->pcap);
    }
    do_abort = 1;
    return NULL;
}