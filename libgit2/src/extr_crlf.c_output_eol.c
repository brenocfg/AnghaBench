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
struct crlf_attrs {int crlf_action; int /*<<< orphan*/  core_eol; } ;
typedef  int /*<<< orphan*/  git_configmap_value ;

/* Variables and functions */
#define  GIT_CRLF_AUTO 135 
#define  GIT_CRLF_AUTO_CRLF 134 
#define  GIT_CRLF_AUTO_INPUT 133 
#define  GIT_CRLF_BINARY 132 
#define  GIT_CRLF_TEXT 131 
#define  GIT_CRLF_TEXT_CRLF 130 
#define  GIT_CRLF_TEXT_INPUT 129 
#define  GIT_CRLF_UNDEFINED 128 
 int /*<<< orphan*/  GIT_EOL_CRLF ; 
 int /*<<< orphan*/  GIT_EOL_LF ; 
 int /*<<< orphan*/  GIT_EOL_UNSET ; 
 int /*<<< orphan*/  text_eol_is_crlf (struct crlf_attrs*) ; 

__attribute__((used)) static git_configmap_value output_eol(struct crlf_attrs *ca)
{
	switch (ca->crlf_action) {
	case GIT_CRLF_BINARY:
		return GIT_EOL_UNSET;
	case GIT_CRLF_TEXT_CRLF:
		return GIT_EOL_CRLF;
	case GIT_CRLF_TEXT_INPUT:
		return GIT_EOL_LF;
	case GIT_CRLF_UNDEFINED:
	case GIT_CRLF_AUTO_CRLF:
		return GIT_EOL_CRLF;
	case GIT_CRLF_AUTO_INPUT:
		return GIT_EOL_LF;
	case GIT_CRLF_TEXT:
	case GIT_CRLF_AUTO:
		return text_eol_is_crlf(ca) ? GIT_EOL_CRLF : GIT_EOL_LF;
	}

	/* TODO: warn when available */
	return ca->core_eol;
}