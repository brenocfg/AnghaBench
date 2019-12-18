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
struct jobspec_hdr {int dummy; } ;
struct jobspec {struct jobspec* matcheduser; struct jobspec* fmtoutput; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (struct jobspec_hdr*) ; 
 struct jobspec* STAILQ_FIRST (struct jobspec_hdr*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct jobspec_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct jobspec*) ; 
 int /*<<< orphan*/  nextjs ; 

void
free_jobspec(struct jobspec_hdr *js_hdr)
{
	struct jobspec *jsinf;

	while (!STAILQ_EMPTY(js_hdr)) {
		jsinf = STAILQ_FIRST(js_hdr);
		STAILQ_REMOVE_HEAD(js_hdr, nextjs);
		if (jsinf->fmtoutput)
			free(jsinf->fmtoutput);
		if (jsinf->matcheduser)
			free(jsinf->matcheduser);
		free(jsinf);
	}
}