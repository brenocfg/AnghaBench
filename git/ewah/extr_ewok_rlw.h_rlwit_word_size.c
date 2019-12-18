#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t running_len; size_t literal_words; } ;
struct rlw_iterator {TYPE_1__ rlw; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t rlwit_word_size(struct rlw_iterator *it)
{
	return it->rlw.running_len + it->rlw.literal_words;
}