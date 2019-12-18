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
typedef  scalar_t__ follby ;

/* Variables and functions */
 scalar_t__ FOLLBY_NON_ACCEPTING ; 
 int SCANNER_INIT_S ; 
 char SS_CH (int /*<<< orphan*/ ) ; 
 scalar_t__ SS_FB (int /*<<< orphan*/ ) ; 
 int SS_MATCH_N (int /*<<< orphan*/ ) ; 
 int SS_OTHER_N (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sst ; 

__attribute__((used)) static int
is_keyword(
	char *lexeme,
	follby *pfollowedby
	)
{
	follby fb;
	int curr_s;		/* current state index */
	int token;
	int i;

	curr_s = SCANNER_INIT_S;
	token = 0;

	for (i = 0; lexeme[i]; i++) {
		while (curr_s && (lexeme[i] != SS_CH(sst[curr_s])))
			curr_s = SS_OTHER_N(sst[curr_s]);

		if (curr_s && (lexeme[i] == SS_CH(sst[curr_s]))) {
			if ('\0' == lexeme[i + 1]
			    && FOLLBY_NON_ACCEPTING 
			       != SS_FB(sst[curr_s])) {
				fb = SS_FB(sst[curr_s]);
				*pfollowedby = fb;
				token = curr_s;
				break;
			}
			curr_s = SS_MATCH_N(sst[curr_s]);
		} else
			break;
	}

	return token;
}