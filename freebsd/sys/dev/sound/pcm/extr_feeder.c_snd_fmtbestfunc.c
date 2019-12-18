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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  score_cheq (scalar_t__,scalar_t__) ; 
 scalar_t__ score_chgt (scalar_t__,scalar_t__) ; 
 scalar_t__ score_chlt (scalar_t__,scalar_t__) ; 
 scalar_t__ score_cse (scalar_t__) ; 
 scalar_t__ score_endianeq (scalar_t__,scalar_t__) ; 
 scalar_t__ score_signeq (scalar_t__,scalar_t__) ; 
 scalar_t__ score_val (scalar_t__) ; 
 scalar_t__ snd_fmtscore (scalar_t__) ; 
 scalar_t__ snd_fmtvalid (scalar_t__,scalar_t__*) ; 

__attribute__((used)) static u_int32_t
snd_fmtbestfunc(u_int32_t fmt, u_int32_t *fmts, int cheq)
{
	u_int32_t best, score, score2, oldscore;
	int i;

	if (fmt == 0 || fmts == NULL || fmts[0] == 0)
		return 0;

	if (snd_fmtvalid(fmt, fmts))
		return fmt;

	best = 0;
	score = snd_fmtscore(fmt);
	oldscore = 0;
	for (i = 0; fmts[i] != 0; i++) {
		score2 = snd_fmtscore(fmts[i]);
		if (cheq && !score_cheq(score, score2) &&
		    (score_chlt(score2, score) ||
		    (oldscore != 0 && score_chgt(score2, oldscore))))
				continue;
		if (oldscore == 0 ||
			    (score_val(score2) == score_val(score)) ||
			    (score_val(score2) == score_val(oldscore)) ||
			    (score_val(score2) > score_val(oldscore) &&
			    score_val(score2) < score_val(score)) ||
			    (score_val(score2) < score_val(oldscore) &&
			    score_val(score2) > score_val(score)) ||
			    (score_val(oldscore) < score_val(score) &&
			    score_val(score2) > score_val(oldscore))) {
			if (score_val(oldscore) != score_val(score2) ||
				    score_cse(score) == score_cse(score2) ||
				    ((score_cse(oldscore) != score_cse(score) &&
				    !score_endianeq(score, oldscore) &&
				    (score_endianeq(score, score2) ||
				    (!score_signeq(score, oldscore) &&
				    score_signeq(score, score2)))))) {
				best = fmts[i];
				oldscore = score2;
			}
		}
	}
	return best;
}