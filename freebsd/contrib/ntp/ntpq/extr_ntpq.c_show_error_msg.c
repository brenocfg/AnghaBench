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
typedef  int associd_t ;

/* Variables and functions */
#define  CERR_BADASSOC 137 
#define  CERR_BADFMT 136 
#define  CERR_BADOP 135 
#define  CERR_BADVALUE 134 
#define  CERR_PERMISSION 133 
#define  CERR_UNKNOWNVAR 132 
#define  ERR_INCOMPLETE 131 
#define  ERR_TIMEOUT 130 
#define  ERR_TOOMUCH 129 
#define  ERR_UNSPEC 128 
 char* currenthost ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int numhosts ; 
 int /*<<< orphan*/  stderr ; 

void
show_error_msg(
	int		m6resp,
	associd_t	associd
	)
{
	if (numhosts > 1)
		fprintf(stderr, "server=%s ", currenthost);

	switch (m6resp) {

	case CERR_BADFMT:
		fprintf(stderr,
		    "***Server reports a bad format request packet\n");
		break;

	case CERR_PERMISSION:
		fprintf(stderr,
		    "***Server disallowed request (authentication?)\n");
		break;

	case CERR_BADOP:
		fprintf(stderr,
		    "***Server reports a bad opcode in request\n");
		break;

	case CERR_BADASSOC:
		fprintf(stderr,
		    "***Association ID %d unknown to server\n",
		    associd);
		break;

	case CERR_UNKNOWNVAR:
		fprintf(stderr,
		    "***A request variable unknown to the server\n");
		break;

	case CERR_BADVALUE:
		fprintf(stderr,
		    "***Server indicates a request variable was bad\n");
		break;

	case ERR_UNSPEC:
		fprintf(stderr,
		    "***Server returned an unspecified error\n");
		break;

	case ERR_TIMEOUT:
		fprintf(stderr, "***Request timed out\n");
		break;

	case ERR_INCOMPLETE:
		fprintf(stderr,
		    "***Response from server was incomplete\n");
		break;

	case ERR_TOOMUCH:
		fprintf(stderr,
		    "***Buffer size exceeded for returned data\n");
		break;

	default:
		fprintf(stderr,
		    "***Server returns unknown error code %d\n",
		    m6resp);
	}
}