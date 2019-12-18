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
struct wtap_medium {int /*<<< orphan*/  md_mtx; int /*<<< orphan*/  md_pktbuf; } ;
struct packet {int dummy; } ;

/* Variables and functions */
 struct packet* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_list ; 

struct packet *
medium_get_next_packet(struct wtap_medium *md)
{
	struct packet *p;

	mtx_lock(&md->md_mtx);
	p = STAILQ_FIRST(&md->md_pktbuf);
	if (p == NULL){
		mtx_unlock(&md->md_mtx);
		return NULL;
	}

	STAILQ_REMOVE_HEAD(&md->md_pktbuf, pf_list);
	mtx_unlock(&md->md_mtx);
	return p;
}