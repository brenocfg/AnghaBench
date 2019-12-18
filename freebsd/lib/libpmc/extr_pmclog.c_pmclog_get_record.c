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
typedef  int /*<<< orphan*/  uint32_t ;
struct pmclog_parse_state {int ps_state; int ps_svcount; int /*<<< orphan*/  ps_saved; } ;
typedef  int ssize_t ;
typedef  enum pmclog_parser_state { ____Placeholder_pmclog_parser_state } pmclog_parser_state ;

/* Variables and functions */
 void* PL_STATE_ERROR ; 
#define  PL_STATE_EXPECTING_HEADER 130 
#define  PL_STATE_NEW_RECORD 129 
#define  PL_STATE_PARTIAL_RECORD 128 
 int /*<<< orphan*/  PMCLOG_HEADER_FROM_SAVED_STATE (struct pmclog_parse_state*) ; 
 int PMCLOG_HEADER_TO_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 

__attribute__((used)) static enum pmclog_parser_state
pmclog_get_record(struct pmclog_parse_state *ps, char **data, ssize_t *len)
{
	int avail, copylen, recordsize, used;
	uint32_t h;
	const int HEADERSIZE = sizeof(uint32_t);
	char *src, *dst;

	if ((avail = *len) <= 0)
		return (ps->ps_state = PL_STATE_ERROR);

	src = *data;
	used = 0;

	if (ps->ps_state == PL_STATE_NEW_RECORD)
		ps->ps_svcount = 0;

	dst = (char *) &ps->ps_saved + ps->ps_svcount;

	switch (ps->ps_state) {
	case PL_STATE_NEW_RECORD:

		/*
		 * Transitions:
		 *
		 * Case A: avail < headersize
		 *	-> 'expecting header'
		 *
		 * Case B: avail >= headersize
		 *    B.1: avail < recordsize
		 *	   -> 'partial record'
		 *    B.2: avail >= recordsize
		 *         -> 'new record'
		 */

		copylen = avail < HEADERSIZE ? avail : HEADERSIZE;
		bcopy(src, dst, copylen);
		ps->ps_svcount = used = copylen;

		if (copylen < HEADERSIZE) {
			ps->ps_state = PL_STATE_EXPECTING_HEADER;
			goto done;
		}

		src += copylen;
		dst += copylen;

		h = PMCLOG_HEADER_FROM_SAVED_STATE(ps);
		recordsize = PMCLOG_HEADER_TO_LENGTH(h);

		if (recordsize <= 0)
			goto error;

		if (recordsize <= avail) { /* full record available */
			bcopy(src, dst, recordsize - copylen);
			ps->ps_svcount = used = recordsize;
			goto done;
		}

		/* header + a partial record is available */
		bcopy(src, dst, avail - copylen);
		ps->ps_svcount = used = avail;
		ps->ps_state = PL_STATE_PARTIAL_RECORD;

		break;

	case PL_STATE_EXPECTING_HEADER:

		/*
		 * Transitions:
		 *
		 * Case C: avail+saved < headersize
		 * 	-> 'expecting header'
		 *
		 * Case D: avail+saved >= headersize
		 *    D.1: avail+saved < recordsize
		 *    	-> 'partial record'
		 *    D.2: avail+saved >= recordsize
		 *    	-> 'new record'
		 *    (see PARTIAL_RECORD handling below)
		 */

		if (avail + ps->ps_svcount < HEADERSIZE) {
			bcopy(src, dst, avail);
			ps->ps_svcount += avail;
			used = avail;
			break;
		}

		used = copylen = HEADERSIZE - ps->ps_svcount;
		bcopy(src, dst, copylen);
		src += copylen;
		dst += copylen;
		avail -= copylen;
		ps->ps_svcount += copylen;

		/*FALLTHROUGH*/

	case PL_STATE_PARTIAL_RECORD:

		/*
		 * Transitions:
		 *
		 * Case E: avail+saved < recordsize
		 * 	-> 'partial record'
		 *
		 * Case F: avail+saved >= recordsize
		 * 	-> 'new record'
		 */

		h = PMCLOG_HEADER_FROM_SAVED_STATE(ps);
		recordsize = PMCLOG_HEADER_TO_LENGTH(h);

		if (recordsize <= 0)
			goto error;

		if (avail + ps->ps_svcount < recordsize) {
			copylen = avail;
			ps->ps_state = PL_STATE_PARTIAL_RECORD;
		} else {
			copylen = recordsize - ps->ps_svcount;
			ps->ps_state = PL_STATE_NEW_RECORD;
		}

		bcopy(src, dst, copylen);
		ps->ps_svcount += copylen;
		used += copylen;
		break;

	default:
		goto error;
	}

 done:
	*data += used;
	*len  -= used;
	return ps->ps_state;

 error:
	ps->ps_state = PL_STATE_ERROR;
	return ps->ps_state;
}