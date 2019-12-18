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
struct pf_osfp_entry {int /*<<< orphan*/  fp_oses; } ;
struct pf_os_fingerprint {int /*<<< orphan*/  fp_oses; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PFOSFP ; 
 struct pf_osfp_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_osfp_list ; 
 int /*<<< orphan*/  fp_entry ; 
 int /*<<< orphan*/  fp_next ; 
 int /*<<< orphan*/  free (struct pf_osfp_entry*,int /*<<< orphan*/ ) ; 

void
pf_osfp_flush(void)
{
	struct pf_os_fingerprint *fp;
	struct pf_osfp_entry *entry;

	while ((fp = SLIST_FIRST(&V_pf_osfp_list))) {
		SLIST_REMOVE_HEAD(&V_pf_osfp_list, fp_next);
		while ((entry = SLIST_FIRST(&fp->fp_oses))) {
			SLIST_REMOVE_HEAD(&fp->fp_oses, fp_entry);
			free(entry, M_PFOSFP);
		}
		free(fp, M_PFOSFP);
	}
}