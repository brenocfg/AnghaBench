#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ seq_t ;
struct TYPE_17__ {scalar_t__ e_c; } ;
struct TYPE_16__ {TYPE_1__* gp; } ;
struct TYPE_15__ {scalar_t__* input; scalar_t__ stype; size_t ilen; } ;
struct TYPE_14__ {int /*<<< orphan*/  seqq; } ;
typedef  TYPE_2__ SEQ ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ EVENT ;
typedef  scalar_t__ CHAR_T ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int MEMCMP (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 int /*<<< orphan*/  SEQ_FUNCMAP ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ ) ; 
 TYPE_2__* SLIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int e_memcmp (scalar_t__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q ; 

SEQ *
seq_find(
	SCR *sp,
	SEQ **lastqp,
	EVENT *e_input,
	CHAR_T *c_input,
	size_t ilen,
	seq_t stype,
	int *ispartialp)
{
	SEQ *lqp = NULL, *qp;
	int diff;

	/*
	 * Ispartialp is a location where we return if there was a
	 * partial match, i.e. if the string were extended it might
	 * match something.
	 *
	 * XXX
	 * Overload the meaning of ispartialp; only the terminal key
	 * search doesn't want the search limited to complete matches,
	 * i.e. ilen may be longer than the match.
	 */
	if (ispartialp != NULL)
		*ispartialp = 0;
	for (qp = SLIST_FIRST(sp->gp->seqq); qp != NULL;
	    lqp = qp, qp = SLIST_NEXT(qp, q)) {
		/*
		 * Fast checks on the first character and type, and then
		 * a real comparison.
		 */
		if (e_input == NULL) {
			if (qp->input[0] > c_input[0])
				break;
			if (qp->input[0] < c_input[0] ||
			    qp->stype != stype || F_ISSET(qp, SEQ_FUNCMAP))
				continue;
			diff = MEMCMP(qp->input, c_input, MIN(qp->ilen, ilen));
		} else {
			if (qp->input[0] > e_input->e_c)
				break;
			if (qp->input[0] < e_input->e_c ||
			    qp->stype != stype || F_ISSET(qp, SEQ_FUNCMAP))
				continue;
			diff =
			    e_memcmp(qp->input, e_input, MIN(qp->ilen, ilen));
		}
		if (diff > 0)
			break;
		if (diff < 0)
			continue;
		/*
		 * If the entry is the same length as the string, return a
		 * match.  If the entry is shorter than the string, return a
		 * match if called from the terminal key routine.  Otherwise,
		 * keep searching for a complete match.
		 */
		if (qp->ilen <= ilen) {
			if (qp->ilen == ilen || ispartialp != NULL) {
				if (lastqp != NULL)
					*lastqp = lqp;
				return (qp);
			}
			continue;
		}
		/*
		 * If the entry longer than the string, return partial match
		 * if called from the terminal key routine.  Otherwise, no
		 * match.
		 */
		if (ispartialp != NULL)
			*ispartialp = 1;
		break;
	}
	if (lastqp != NULL)
		*lastqp = lqp;
	return (NULL);
}