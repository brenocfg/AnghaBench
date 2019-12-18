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
struct unisve_blli_id3 {scalar_t__ proto; scalar_t__ user; scalar_t__ ipi; scalar_t__ oui; scalar_t__ pid; scalar_t__ noipi; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_OVERLAP (struct unisve_blli_id3 const*,struct unisve_blli_id3 const*) ; 
 scalar_t__ UNI_BLLI_L3_SNAP ; 
 scalar_t__ UNI_BLLI_L3_TR9577 ; 
 scalar_t__ UNI_BLLI_L3_USER ; 

int
unisve_overlap_blli_id3(const struct unisve_blli_id3 *s1,
    const struct unisve_blli_id3 *s2)
{
	COMMON_OVERLAP(s1, s2);

	if (s1->proto != s2->proto)
		return (0);
	if (s1->proto == UNI_BLLI_L3_USER)
		return (s1->user == s2->user);
	if (s1->proto == UNI_BLLI_L3_TR9577) {
		if (s1->noipi && s2->noipi)
			return (1);
		if (!s1->noipi && !s2->noipi) {
			if (s1->ipi == s2->ipi) {
				if (s1->ipi != UNI_BLLI_L3_SNAP)
					return (1);
				if (s1->oui == s2->oui && s1->pid == s2->pid)
					return (1);
			}
		}
		return (0);
	}
	return (1);
}