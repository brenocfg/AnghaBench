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
struct index_state {int dummy; } ;
struct conv_attrs {int attr_action; } ;

/* Variables and functions */
#define  CRLF_AUTO 135 
#define  CRLF_AUTO_CRLF 134 
#define  CRLF_AUTO_INPUT 133 
#define  CRLF_BINARY 132 
#define  CRLF_TEXT 131 
#define  CRLF_TEXT_CRLF 130 
#define  CRLF_TEXT_INPUT 129 
#define  CRLF_UNDEFINED 128 
 int /*<<< orphan*/  convert_attrs (struct index_state const*,struct conv_attrs*,char const*) ; 

const char *get_convert_attr_ascii(const struct index_state *istate, const char *path)
{
	struct conv_attrs ca;

	convert_attrs(istate, &ca, path);
	switch (ca.attr_action) {
	case CRLF_UNDEFINED:
		return "";
	case CRLF_BINARY:
		return "-text";
	case CRLF_TEXT:
		return "text";
	case CRLF_TEXT_INPUT:
		return "text eol=lf";
	case CRLF_TEXT_CRLF:
		return "text eol=crlf";
	case CRLF_AUTO:
		return "text=auto";
	case CRLF_AUTO_CRLF:
		return "text=auto eol=crlf";
	case CRLF_AUTO_INPUT:
		return "text=auto eol=lf";
	}
	return "";
}