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
struct nvme_power_state {void* actp; void* idlp; void* exlat; void* enlat; void* mp; } ;

/* Variables and functions */
 void* le16toh (void*) ; 
 void* le32toh (void*) ; 

__attribute__((used)) static inline
void	nvme_power_state_swapbytes(struct nvme_power_state *s)
{

	s->mp = le16toh(s->mp);
	s->enlat = le32toh(s->enlat);
	s->exlat = le32toh(s->exlat);
	s->idlp = le16toh(s->idlp);
	s->actp = le16toh(s->actp);
}