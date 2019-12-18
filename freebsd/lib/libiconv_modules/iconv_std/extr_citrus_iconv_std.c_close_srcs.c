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
struct _citrus_iconv_std_src_list {int dummy; } ;
struct _citrus_iconv_std_src {int /*<<< orphan*/  ss_dsts; } ;

/* Variables and functions */
 struct _citrus_iconv_std_src* TAILQ_FIRST (struct _citrus_iconv_std_src_list*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct _citrus_iconv_std_src_list*,struct _citrus_iconv_std_src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_dsts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct _citrus_iconv_std_src*) ; 
 int /*<<< orphan*/  ss_entry ; 

__attribute__((used)) static void
close_srcs(struct _citrus_iconv_std_src_list *sl)
{
	struct _citrus_iconv_std_src *ss;

	while ((ss = TAILQ_FIRST(sl)) != NULL) {
		TAILQ_REMOVE(sl, ss, ss_entry);
		close_dsts(&ss->ss_dsts);
		free(ss);
	}
}