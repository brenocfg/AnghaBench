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
struct sscfu_sig {int /*<<< orphan*/  m; int /*<<< orphan*/  sig; } ;
struct sscfu {scalar_t__ inhand; int /*<<< orphan*/  sigs; } ;

/* Variables and functions */
 struct sscfu_sig* SIGQ_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIG_FREE (struct sscfu_sig*) ; 
 int /*<<< orphan*/  sscfu_dosig (struct sscfu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sscfu_unqueue(struct sscfu *sscf)
{
	struct sscfu_sig *s;

	while ((s = SIGQ_GET(&sscf->sigs)) != NULL) {
		sscfu_dosig(sscf, s->sig, s->m);
		SIG_FREE(s);
	}
	sscf->inhand = 0;
}