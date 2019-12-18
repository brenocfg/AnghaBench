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
struct line_number_mapping {int dummy; } ;
struct fingerprint {int dummy; } ;

/* Variables and functions */
 int CERTAINTY_NOT_CALCULATED ; 
 int CERTAIN_NOTHING_MATCHES ; 
 int abs (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int fingerprint_similarity (struct fingerprint*,struct fingerprint*) ; 
 int* get_similarity (int*,int,int,int,int const) ; 
 int map_line_number (int,struct line_number_mapping const*) ; 

__attribute__((used)) static void find_best_line_matches(
	int start_a,
	int length_a,
	int start_b,
	int local_line_b,
	struct fingerprint *fingerprints_a,
	struct fingerprint *fingerprints_b,
	int *similarities,
	int *certainties,
	int *second_best_result,
	int *result,
	const int max_search_distance_a,
	const struct line_number_mapping *map_line_number_in_b_to_a)
{

	int i, search_start, search_end, closest_local_line_a, *similarity,
		best_similarity = 0, second_best_similarity = 0,
		best_similarity_index = 0, second_best_similarity_index = 0;

	/* certainty has already been calculated so no need to redo the work */
	if (certainties[local_line_b] != CERTAINTY_NOT_CALCULATED)
		return;

	closest_local_line_a = map_line_number(
		local_line_b + start_b, map_line_number_in_b_to_a) - start_a;

	search_start = closest_local_line_a - max_search_distance_a;
	if (search_start < 0)
		search_start = 0;

	search_end = closest_local_line_a + max_search_distance_a + 1;
	if (search_end > length_a)
		search_end = length_a;

	for (i = search_start; i < search_end; ++i) {
		similarity = get_similarity(similarities,
					    i, local_line_b,
					    closest_local_line_a,
					    max_search_distance_a);
		if (*similarity == -1) {
			/* This value will never exceed 10 but assert just in
			 * case
			 */
			assert(abs(i - closest_local_line_a) < 1000);
			/* scale the similarity by (1000 - distance from
			 * closest line) to act as a tie break between lines
			 * that otherwise are equally similar.
			 */
			*similarity = fingerprint_similarity(
				fingerprints_b + local_line_b,
				fingerprints_a + i) *
				(1000 - abs(i - closest_local_line_a));
		}
		if (*similarity > best_similarity) {
			second_best_similarity = best_similarity;
			second_best_similarity_index = best_similarity_index;
			best_similarity = *similarity;
			best_similarity_index = i;
		} else if (*similarity > second_best_similarity) {
			second_best_similarity = *similarity;
			second_best_similarity_index = i;
		}
	}

	if (best_similarity == 0) {
		/* this line definitely doesn't match with anything. Mark it
		 * with this special value so it doesn't get invalidated and
		 * won't be recalculated.
		 */
		certainties[local_line_b] = CERTAIN_NOTHING_MATCHES;
		result[local_line_b] = -1;
	} else {
		/* Calculate the certainty with which this line matches.
		 * If the line matches well with two lines then that reduces
		 * the certainty. However we still want to prioritise matching
		 * a line that matches very well with two lines over matching a
		 * line that matches poorly with one line, hence doubling
		 * best_similarity.
		 * This means that if we have
		 * line X that matches only one line with a score of 3,
		 * line Y that matches two lines equally with a score of 5,
		 * and line Z that matches only one line with a score or 2,
		 * then the lines in order of certainty are X, Y, Z.
		 */
		certainties[local_line_b] = best_similarity * 2 -
			second_best_similarity;

		/* We keep both the best and second best results to allow us to
		 * check at a later stage of the matching process whether the
		 * result needs to be invalidated.
		 */
		result[local_line_b] = start_a + best_similarity_index;
		second_best_result[local_line_b] =
			start_a + second_best_similarity_index;
	}
}