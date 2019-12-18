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
struct cryptoini {int /*<<< orphan*/  cri_alg; struct cryptoini* cri_next; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ sec_mdeu_can_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sec_split_cri(struct cryptoini *cri, struct cryptoini **enc,
    struct cryptoini **mac)
{
	struct cryptoini *e, *m;

	e = cri;
	m = cri->cri_next;

	/* We can haldle only two operations */
	if (m && m->cri_next)
		return (EINVAL);

	if (sec_mdeu_can_handle(e->cri_alg)) {
		cri = m;
		m = e;
		e = cri;
	}

	if (m && !sec_mdeu_can_handle(m->cri_alg))
		return (EINVAL);

	*enc = e;
	*mac = m;

	return (0);
}