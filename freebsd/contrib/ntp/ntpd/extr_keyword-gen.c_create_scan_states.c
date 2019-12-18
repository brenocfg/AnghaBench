#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_short ;
typedef  scalar_t__ follby ;
struct TYPE_4__ {char ch; size_t other_next_s; size_t finishes_token; char followedby; size_t match_next_s; } ;

/* Variables and functions */
 size_t COUNTOF (TYPE_1__*) ; 
 char FOLLBY_NON_ACCEPTING ; 
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 char* current_keyword ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* sst ; 
 size_t sst_highwater ; 
 int /*<<< orphan*/  stderr ; 
 char* symbname (size_t) ; 

__attribute__((used)) static u_short
create_scan_states(
	char *	text,
	u_short	token,
	follby	followedby,
	u_short	prev_state
	)
{
	u_short my_state;
	u_short return_state;
	u_short prev_char_s;
	u_short curr_char_s;

	return_state = prev_state;
	curr_char_s = prev_state;
	prev_char_s = 0;

	/* Find the correct position to insert the state.
	 * All states should be in alphabetical order
	 */
	while (curr_char_s && (text[0] < sst[curr_char_s].ch)) {
		prev_char_s = curr_char_s;
		curr_char_s = sst[curr_char_s].other_next_s;
	}

	/*
	 * Check if a previously seen keyword has the same prefix as
	 * the current keyword.  If so, simply use the state for that
	 * keyword as my_state, otherwise, allocate a new state.
	 */
	if (curr_char_s && (text[0] == sst[curr_char_s].ch)) {
		my_state = curr_char_s;
		if ('\0' == text[1]) {
			fprintf(stderr,
				"Duplicate entries for keyword '%s' in"
				" keyword_gen.c ntp_keywords[].\n",
				current_keyword);
			exit(2);
		}
	} else {
		do
			my_state = sst_highwater++;
		while (my_state < COUNTOF(sst)
		       && sst[my_state].finishes_token);
		if (my_state >= COUNTOF(sst)) {
			fprintf(stderr,
				"fatal, keyword scanner state array "
				"sst[%d] is too small, modify\n"
				"keyword-gen.c to increase.\n",
				(int)COUNTOF(sst));
			exit(3);
		}
		/* Store the next character of the keyword */
		sst[my_state].ch = text[0];
		sst[my_state].other_next_s = curr_char_s;
		sst[my_state].followedby = FOLLBY_NON_ACCEPTING;

		if (prev_char_s)
			sst[prev_char_s].other_next_s = my_state;
		else
			return_state = my_state;
	}

	/* Check if the next character is '\0'.
	 * If yes, we are done with the recognition and this is an accepting
	 * state.
	 * If not, we need to continue scanning
	 */
	if ('\0' == text[1]) {
		sst[my_state].finishes_token = (u_short)token;
		sst[my_state].followedby = (char)followedby;

		if (sst[token].finishes_token != (u_short)token) {
			fprintf(stderr,
				"fatal, sst[%d] not reserved for %s.\n",
				token, symbname(token));
			exit(6);
		}
		/* relocate so token id is sst[] index */
		if (my_state != token) {
			sst[token] = sst[my_state];
			ZERO(sst[my_state]);
			do
				sst_highwater--;
			while (sst[sst_highwater].finishes_token);
			my_state = token;
			if (prev_char_s)
				sst[prev_char_s].other_next_s = my_state;
			else
				return_state = my_state;
		}
	} else
		sst[my_state].match_next_s =
		    create_scan_states(
			&text[1],
			token,
			followedby,
			sst[my_state].match_next_s);

	return return_state;
}