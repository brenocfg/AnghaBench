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
struct nvme_controller_data {int /*<<< orphan*/ * power_state; void* mnan; void* sgls; void* acwu; void* awupf; void* awun; void* fuses; void* oncs; void* nn; void* maxcmd; void* pels; void* nanagrpid; void* anagrpmax; void* endgidmax; void* nsetidmax; void* hmmaxd; void* hmminds; void* sanicap; void* mxtmt; void* mntmt; void* hctma; void* kas; void* edstt; void* rpmbs; void* hmmin; void* hmpre; void* mtfa; void* cctemp; void* wctemp; void* oacs; void* crdt3; void* crdt2; void* crdt1; void* rrls; void* ctratt; void* oaes; void* rtd3e; void* rtd3r; void* ver; void* ctrlr_id; void* ssvid; void* vid; } ;

/* Variables and functions */
 void* le16toh (void*) ; 
 void* le32toh (void*) ; 
 int /*<<< orphan*/  nvme_power_state_swapbytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void	nvme_controller_data_swapbytes(struct nvme_controller_data *s)
{
	int i;

	s->vid = le16toh(s->vid);
	s->ssvid = le16toh(s->ssvid);
	s->ctrlr_id = le16toh(s->ctrlr_id);
	s->ver = le32toh(s->ver);
	s->rtd3r = le32toh(s->rtd3r);
	s->rtd3e = le32toh(s->rtd3e);
	s->oaes = le32toh(s->oaes);
	s->ctratt = le32toh(s->ctratt);
	s->rrls = le16toh(s->rrls);
	s->crdt1 = le16toh(s->crdt1);
	s->crdt2 = le16toh(s->crdt2);
	s->crdt3 = le16toh(s->crdt3);
	s->oacs = le16toh(s->oacs);
	s->wctemp = le16toh(s->wctemp);
	s->cctemp = le16toh(s->cctemp);
	s->mtfa = le16toh(s->mtfa);
	s->hmpre = le32toh(s->hmpre);
	s->hmmin = le32toh(s->hmmin);
	s->rpmbs = le32toh(s->rpmbs);
	s->edstt = le16toh(s->edstt);
	s->kas = le16toh(s->kas);
	s->hctma = le16toh(s->hctma);
	s->mntmt = le16toh(s->mntmt);
	s->mxtmt = le16toh(s->mxtmt);
	s->sanicap = le32toh(s->sanicap);
	s->hmminds = le32toh(s->hmminds);
	s->hmmaxd = le16toh(s->hmmaxd);
	s->nsetidmax = le16toh(s->nsetidmax);
	s->endgidmax = le16toh(s->endgidmax);
	s->anagrpmax = le32toh(s->anagrpmax);
	s->nanagrpid = le32toh(s->nanagrpid);
	s->pels = le32toh(s->pels);
	s->maxcmd = le16toh(s->maxcmd);
	s->nn = le32toh(s->nn);
	s->oncs = le16toh(s->oncs);
	s->fuses = le16toh(s->fuses);
	s->awun = le16toh(s->awun);
	s->awupf = le16toh(s->awupf);
	s->acwu = le16toh(s->acwu);
	s->sgls = le32toh(s->sgls);
	s->mnan = le32toh(s->mnan);
	for (i = 0; i < 32; i++)
		nvme_power_state_swapbytes(&s->power_state[i]);
}