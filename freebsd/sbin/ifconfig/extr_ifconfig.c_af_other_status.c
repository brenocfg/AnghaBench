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
typedef  int /*<<< orphan*/  uint8_t ;
struct afswtch {scalar_t__ af_af; int /*<<< orphan*/  (* af_other_status ) (int) ;struct afswtch* af_next; } ;
typedef  int /*<<< orphan*/  afmask ;

/* Variables and functions */
 int /*<<< orphan*/  AF_MAX ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  NBBY ; 
 struct afswtch* afs ; 
 int howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isset (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
af_other_status(int s)
{
	struct afswtch *afp;
	uint8_t afmask[howmany(AF_MAX, NBBY)];

	memset(afmask, 0, sizeof(afmask));
	for (afp = afs; afp != NULL; afp = afp->af_next) {
		if (afp->af_other_status == NULL)
			continue;
		if (afp->af_af != AF_UNSPEC && isset(afmask, afp->af_af))
			continue;
		afp->af_other_status(s);
		setbit(afmask, afp->af_af);
	}
}