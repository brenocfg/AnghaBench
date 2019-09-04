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
struct ewah_bitmap {int dummy; } ;
struct bitmap {size_t word_alloc; scalar_t__* words; } ;
typedef  scalar_t__ eword_t ;

/* Variables and functions */
 int /*<<< orphan*/  ewah_add (struct ewah_bitmap*,scalar_t__) ; 
 int /*<<< orphan*/  ewah_add_empty_words (struct ewah_bitmap*,int /*<<< orphan*/ ,size_t) ; 
 struct ewah_bitmap* ewah_new () ; 

struct ewah_bitmap *bitmap_to_ewah(struct bitmap *bitmap)
{
	struct ewah_bitmap *ewah = ewah_new();
	size_t i, running_empty_words = 0;
	eword_t last_word = 0;

	for (i = 0; i < bitmap->word_alloc; ++i) {
		if (bitmap->words[i] == 0) {
			running_empty_words++;
			continue;
		}

		if (last_word != 0)
			ewah_add(ewah, last_word);

		if (running_empty_words > 0) {
			ewah_add_empty_words(ewah, 0, running_empty_words);
			running_empty_words = 0;
		}

		last_word = bitmap->words[i];
	}

	ewah_add(ewah, last_word);
	return ewah;
}