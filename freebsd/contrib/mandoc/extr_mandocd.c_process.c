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
struct roff_meta {scalar_t__ macroset; } ;
struct mparse {int dummy; } ;
typedef  enum outt { ____Placeholder_outt } outt ;

/* Variables and functions */
 scalar_t__ MACROSET_MAN ; 
 scalar_t__ MACROSET_MDOC ; 
#define  OUTT_ASCII 130 
#define  OUTT_HTML 129 
#define  OUTT_UTF8 128 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  html_man (void*,struct roff_meta*) ; 
 int /*<<< orphan*/  html_mdoc (void*,struct roff_meta*) ; 
 int /*<<< orphan*/  mparse_readfd (struct mparse*,int /*<<< orphan*/ ,char*) ; 
 struct roff_meta* mparse_result (struct mparse*) ; 
 int /*<<< orphan*/  terminal_man (void*,struct roff_meta*) ; 
 int /*<<< orphan*/  terminal_mdoc (void*,struct roff_meta*) ; 

__attribute__((used)) static void
process(struct mparse *parser, enum outt outtype, void *formatter)
{
	struct roff_meta *meta;

	mparse_readfd(parser, STDIN_FILENO, "<unixfd>");
	meta = mparse_result(parser);
	if (meta->macroset == MACROSET_MDOC) {
		switch (outtype) {
		case OUTT_ASCII:
		case OUTT_UTF8:
			terminal_mdoc(formatter, meta);
			break;
		case OUTT_HTML:
			html_mdoc(formatter, meta);
			break;
		}
	}
	if (meta->macroset == MACROSET_MAN) {
		switch (outtype) {
		case OUTT_ASCII:
		case OUTT_UTF8:
			terminal_man(formatter, meta);
			break;
		case OUTT_HTML:
			html_man(formatter, meta);
			break;
		}
	}
}