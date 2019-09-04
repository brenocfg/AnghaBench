#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  hashsig_t ;
typedef  scalar_t__ hashsig_state ;
struct TYPE_5__ {int use_ignores; } ;
typedef  TYPE_1__ hashsig_in_progress ;
struct TYPE_6__ {int opt; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  lines; } ;
typedef  TYPE_2__ git_hashsig ;

/* Variables and functions */
 int GIT_HASHSIG_IGNORE_WHITESPACE ; 
 int GIT_HASHSIG_SMART_WHITESPACE ; 
 int /*<<< orphan*/  HASHSIG_HASH_MIX (scalar_t__,char) ; 
 scalar_t__ HASHSIG_HASH_START ; 
 int HASHSIG_MAX_RUN ; 
 scalar_t__ git__isspace_nonlf (char) ; 
 int /*<<< orphan*/  hashsig_heap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hashsig_add_hashes(
	git_hashsig *sig,
	const uint8_t *data,
	size_t size,
	hashsig_in_progress *prog)
{
	const uint8_t *scan = data, *end = data + size;
	hashsig_state state = HASHSIG_HASH_START;
	int use_ignores = prog->use_ignores, len;
	uint8_t ch;

	while (scan < end) {
		state = HASHSIG_HASH_START;

		for (len = 0; scan < end && len < HASHSIG_MAX_RUN; ) {
			ch = *scan;

			if (use_ignores)
				for (; scan < end && git__isspace_nonlf(ch); ch = *scan)
					++scan;
			else if (sig->opt &
					 (GIT_HASHSIG_IGNORE_WHITESPACE | GIT_HASHSIG_SMART_WHITESPACE))
				for (; scan < end && ch == '\r'; ch = *scan)
					++scan;

			/* peek at next character to decide what to do next */
			if (sig->opt & GIT_HASHSIG_SMART_WHITESPACE)
				use_ignores = (ch == '\n');

			if (scan >= end)
				break;
			++scan;

			/* check run terminator */
			if (ch == '\n' || ch == '\0') {
				sig->lines++;
				break;
			}

			++len;
			HASHSIG_HASH_MIX(state, ch);
		}

		if (len > 0) {
			hashsig_heap_insert(&sig->mins, (hashsig_t)state);
			hashsig_heap_insert(&sig->maxs, (hashsig_t)state);

			while (scan < end && (*scan == '\n' || !*scan))
				++scan;
		}
	}

	prog->use_ignores = use_ignores;

	return 0;
}