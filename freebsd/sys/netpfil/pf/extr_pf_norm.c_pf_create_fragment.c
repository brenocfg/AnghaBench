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
typedef  int /*<<< orphan*/  u_short ;
struct pf_frent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PFRES_MEMORY ; 
 int /*<<< orphan*/  PF_FRAG_ASSERT () ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_frent_z ; 
 int /*<<< orphan*/  pf_flush_fragments () ; 
 struct pf_frent* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pf_frent *
pf_create_fragment(u_short *reason)
{
	struct pf_frent *frent;

	PF_FRAG_ASSERT();

	frent = uma_zalloc(V_pf_frent_z, M_NOWAIT);
	if (frent == NULL) {
		pf_flush_fragments();
		frent = uma_zalloc(V_pf_frent_z, M_NOWAIT);
		if (frent == NULL) {
			REASON_SET(reason, PFRES_MEMORY);
			return (NULL);
		}
	}

	return (frent);
}