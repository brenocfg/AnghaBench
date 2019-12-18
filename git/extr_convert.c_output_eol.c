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
typedef  enum eol { ____Placeholder_eol } eol ;
typedef  enum crlf_action { ____Placeholder_crlf_action } crlf_action ;

/* Variables and functions */
#define  CRLF_AUTO 135 
#define  CRLF_AUTO_CRLF 134 
#define  CRLF_AUTO_INPUT 133 
#define  CRLF_BINARY 132 
#define  CRLF_TEXT 131 
#define  CRLF_TEXT_CRLF 130 
#define  CRLF_TEXT_INPUT 129 
#define  CRLF_UNDEFINED 128 
 int EOL_CRLF ; 
 int EOL_LF ; 
 int EOL_UNSET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int core_eol ; 
 int /*<<< orphan*/  text_eol_is_crlf () ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum eol output_eol(enum crlf_action crlf_action)
{
	switch (crlf_action) {
	case CRLF_BINARY:
		return EOL_UNSET;
	case CRLF_TEXT_CRLF:
		return EOL_CRLF;
	case CRLF_TEXT_INPUT:
		return EOL_LF;
	case CRLF_UNDEFINED:
	case CRLF_AUTO_CRLF:
		return EOL_CRLF;
	case CRLF_AUTO_INPUT:
		return EOL_LF;
	case CRLF_TEXT:
	case CRLF_AUTO:
		/* fall through */
		return text_eol_is_crlf() ? EOL_CRLF : EOL_LF;
	}
	warning(_("illegal crlf_action %d"), (int)crlf_action);
	return core_eol;
}