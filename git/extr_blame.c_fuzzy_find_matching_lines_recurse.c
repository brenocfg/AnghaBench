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
 int abs (int) ; 
 int /*<<< orphan*/  find_best_line_matches (int,int,int,int,struct fingerprint*,struct fingerprint*,int*,int*,int*,int*,int,struct line_number_mapping const*) ; 
 int /*<<< orphan*/  fingerprint_subtract (struct fingerprint*,struct fingerprint*) ; 
 int* get_similarity (int*,int,int,int,int) ; 
 int map_line_number (int,struct line_number_mapping const*) ; 

__attribute__((used)) static void fuzzy_find_matching_lines_recurse(
	int start_a, int start_b,
	int length_a, int length_b,
	struct fingerprint *fingerprints_a,
	struct fingerprint *fingerprints_b,
	int *similarities,
	int *certainties,
	int *second_best_result,
	int *result,
	int max_search_distance_a,
	int max_search_distance_b,
	const struct line_number_mapping *map_line_number_in_b_to_a)
{
	int i, invalidate_min, invalidate_max, offset_b,
		second_half_start_a, second_half_start_b,
		second_half_length_a, second_half_length_b,
		most_certain_line_a, most_certain_local_line_b = -1,
		most_certain_line_certainty = -1,
		closest_local_line_a;

	for (i = 0; i < length_b; ++i) {
		find_best_line_matches(start_a,
				       length_a,
				       start_b,
				       i,
				       fingerprints_a,
				       fingerprints_b,
				       similarities,
				       certainties,
				       second_best_result,
				       result,
				       max_search_distance_a,
				       map_line_number_in_b_to_a);

		if (certainties[i] > most_certain_line_certainty) {
			most_certain_line_certainty = certainties[i];
			most_certain_local_line_b = i;
		}
	}

	/* No matches. */
	if (most_certain_local_line_b == -1)
		return;

	most_certain_line_a = result[most_certain_local_line_b];

	/*
	 * Subtract the most certain line's fingerprint in B from the matched
	 * fingerprint in A. This means that other lines in B can't also match
	 * the same parts of the line in A.
	 */
	fingerprint_subtract(fingerprints_a + most_certain_line_a - start_a,
			     fingerprints_b + most_certain_local_line_b);

	/* Invalidate results that may be affected by the choice of most
	 * certain line.
	 */
	invalidate_min = most_certain_local_line_b - max_search_distance_b;
	invalidate_max = most_certain_local_line_b + max_search_distance_b + 1;
	if (invalidate_min < 0)
		invalidate_min = 0;
	if (invalidate_max > length_b)
		invalidate_max = length_b;

	/* As the fingerprint in A has changed, discard previously calculated
	 * similarity values with that fingerprint.
	 */
	for (i = invalidate_min; i < invalidate_max; ++i) {
		closest_local_line_a = map_line_number(
			i + start_b, map_line_number_in_b_to_a) - start_a;

		/* Check that the lines in A and B are close enough that there
		 * is a similarity value for them.
		 */
		if (abs(most_certain_line_a - start_a - closest_local_line_a) >
			max_search_distance_a) {
			continue;
		}

		*get_similarity(similarities, most_certain_line_a - start_a,
				i, closest_local_line_a,
				max_search_distance_a) = -1;
	}

	/* More invalidating of results that may be affected by the choice of
	 * most certain line.
	 * Discard the matches for lines in B that are currently matched with a
	 * line in A such that their ordering contradicts the ordering imposed
	 * by the choice of most certain line.
	 */
	for (i = most_certain_local_line_b - 1; i >= invalidate_min; --i) {
		/* In this loop we discard results for lines in B that are
		 * before most-certain-line-B but are matched with a line in A
		 * that is after most-certain-line-A.
		 */
		if (certainties[i] >= 0 &&
		    (result[i] >= most_certain_line_a ||
		     second_best_result[i] >= most_certain_line_a)) {
			certainties[i] = CERTAINTY_NOT_CALCULATED;
		}
	}
	for (i = most_certain_local_line_b + 1; i < invalidate_max; ++i) {
		/* In this loop we discard results for lines in B that are
		 * after most-certain-line-B but are matched with a line in A
		 * that is before most-certain-line-A.
		 */
		if (certainties[i] >= 0 &&
		    (result[i] <= most_certain_line_a ||
		     second_best_result[i] <= most_certain_line_a)) {
			certainties[i] = CERTAINTY_NOT_CALCULATED;
		}
	}

	/* Repeat the matching process for lines before the most certain line.
	 */
	if (most_certain_local_line_b > 0) {
		fuzzy_find_matching_lines_recurse(
			start_a, start_b,
			most_certain_line_a + 1 - start_a,
			most_certain_local_line_b,
			fingerprints_a, fingerprints_b, similarities,
			certainties, second_best_result, result,
			max_search_distance_a,
			max_search_distance_b,
			map_line_number_in_b_to_a);
	}
	/* Repeat the matching process for lines after the most certain line.
	 */
	if (most_certain_local_line_b + 1 < length_b) {
		second_half_start_a = most_certain_line_a;
		offset_b = most_certain_local_line_b + 1;
		second_half_start_b = start_b + offset_b;
		second_half_length_a =
			length_a + start_a - second_half_start_a;
		second_half_length_b =
			length_b + start_b - second_half_start_b;
		fuzzy_find_matching_lines_recurse(
			second_half_start_a, second_half_start_b,
			second_half_length_a, second_half_length_b,
			fingerprints_a + second_half_start_a - start_a,
			fingerprints_b + offset_b,
			similarities +
				offset_b * (max_search_distance_a * 2 + 1),
			certainties + offset_b,
			second_best_result + offset_b, result + offset_b,
			max_search_distance_a,
			max_search_distance_b,
			map_line_number_in_b_to_a);
	}
}