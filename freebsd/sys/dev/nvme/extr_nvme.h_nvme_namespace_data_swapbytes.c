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
struct nvme_namespace_data {void** lbaf; void* endgid; void* nvmsetid; void* anagrpid; void* nows; void* npda; void* npdg; void* npwa; void* npwg; void* noiob; void* nabspf; void* nabo; void* nabsn; void* nacwu; void* nawupf; void* nawun; void* nuse; void* ncap; void* nsze; } ;

/* Variables and functions */
 void* le16toh (void*) ; 
 void* le32toh (void*) ; 
 void* le64toh (void*) ; 

__attribute__((used)) static inline
void	nvme_namespace_data_swapbytes(struct nvme_namespace_data *s)
{
	int i;

	s->nsze = le64toh(s->nsze);
	s->ncap = le64toh(s->ncap);
	s->nuse = le64toh(s->nuse);
	s->nawun = le16toh(s->nawun);
	s->nawupf = le16toh(s->nawupf);
	s->nacwu = le16toh(s->nacwu);
	s->nabsn = le16toh(s->nabsn);
	s->nabo = le16toh(s->nabo);
	s->nabspf = le16toh(s->nabspf);
	s->noiob = le16toh(s->noiob);
	s->npwg = le16toh(s->npwg);
	s->npwa = le16toh(s->npwa);
	s->npdg = le16toh(s->npdg);
	s->npda = le16toh(s->npda);
	s->nows = le16toh(s->nows);
	s->anagrpid = le32toh(s->anagrpid);
	s->nvmsetid = le16toh(s->nvmsetid);
	s->endgid = le16toh(s->endgid);
	for (i = 0; i < 16; i++)
		s->lbaf[i] = le32toh(s->lbaf[i]);
}