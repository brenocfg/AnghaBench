#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_tokentype_t ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ isc_token_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_lex_t ;
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 unsigned int ISC_LEXOPT_DNSMULTILINE ; 
 unsigned int ISC_LEXOPT_EOF ; 
 unsigned int ISC_LEXOPT_EOL ; 
 unsigned int ISC_LEXOPT_ESCAPE ; 
 unsigned int ISC_LEXOPT_NUMBER ; 
 unsigned int ISC_LEXOPT_QSTRING ; 
 scalar_t__ ISC_R_BADNUMBER ; 
 scalar_t__ ISC_R_RANGE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ ISC_R_UNEXPECTEDEND ; 
 scalar_t__ ISC_R_UNEXPECTEDTOKEN ; 
 scalar_t__ isc_lex_gettoken (int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  isc_lex_ungettoken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ isc_tokentype_eof ; 
 scalar_t__ isc_tokentype_eol ; 
 scalar_t__ isc_tokentype_number ; 
 scalar_t__ isc_tokentype_qstring ; 
 scalar_t__ isc_tokentype_string ; 

isc_result_t
isc_lex_getmastertoken(isc_lex_t *lex, isc_token_t *token,
		       isc_tokentype_t expect, isc_boolean_t eol)
{
	unsigned int options = ISC_LEXOPT_EOL | ISC_LEXOPT_EOF |
			       ISC_LEXOPT_DNSMULTILINE | ISC_LEXOPT_ESCAPE;
	isc_result_t result;

	if (expect == isc_tokentype_qstring)
		options |= ISC_LEXOPT_QSTRING;
	else if (expect == isc_tokentype_number)
		options |= ISC_LEXOPT_NUMBER;
	result = isc_lex_gettoken(lex, options, token);
	if (result == ISC_R_RANGE)
		isc_lex_ungettoken(lex, token);
	if (result != ISC_R_SUCCESS)
		return (result);

	if (eol && ((token->type == isc_tokentype_eol) ||
		    (token->type == isc_tokentype_eof)))
		return (ISC_R_SUCCESS);
	if (token->type == isc_tokentype_string &&
	    expect == isc_tokentype_qstring)
		return (ISC_R_SUCCESS);
	if (token->type != expect) {
		isc_lex_ungettoken(lex, token);
		if (token->type == isc_tokentype_eol ||
		    token->type == isc_tokentype_eof)
			return (ISC_R_UNEXPECTEDEND);
		if (expect == isc_tokentype_number)
			return (ISC_R_BADNUMBER);
		return (ISC_R_UNEXPECTEDTOKEN);
	}
	return (ISC_R_SUCCESS);
}