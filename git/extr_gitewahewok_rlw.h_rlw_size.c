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
typedef  scalar_t__ eword_t ;

/* Variables and functions */
 scalar_t__ rlw_get_literal_words (scalar_t__ const*) ; 
 scalar_t__ rlw_get_running_len (scalar_t__ const*) ; 

__attribute__((used)) static inline eword_t rlw_size(const eword_t *self)
{
	return rlw_get_running_len(self) + rlw_get_literal_words(self);
}