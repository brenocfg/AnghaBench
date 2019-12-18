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
struct text_stat {scalar_t__ crlf; scalar_t__ lonecr; int /*<<< orphan*/  lonelf; } ;
typedef  enum crlf_action { ____Placeholder_crlf_action } crlf_action ;

/* Variables and functions */
 int CRLF_AUTO ; 
 int CRLF_AUTO_CRLF ; 
 int CRLF_AUTO_INPUT ; 
 scalar_t__ EOL_CRLF ; 
 scalar_t__ convert_is_binary (struct text_stat*) ; 
 scalar_t__ output_eol (int) ; 

__attribute__((used)) static int will_convert_lf_to_crlf(struct text_stat *stats,
				   enum crlf_action crlf_action)
{
	if (output_eol(crlf_action) != EOL_CRLF)
		return 0;
	/* No "naked" LF? Nothing to convert, regardless. */
	if (!stats->lonelf)
		return 0;

	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_AUTO_INPUT || crlf_action == CRLF_AUTO_CRLF) {
		/* If we have any CR or CRLF line endings, we do not touch it */
		/* This is the new safer autocrlf-handling */
		if (stats->lonecr || stats->crlf)
			return 0;

		if (convert_is_binary(stats))
			return 0;
	}
	return 1;

}