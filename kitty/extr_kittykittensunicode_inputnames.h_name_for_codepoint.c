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
typedef  size_t char_type ;

/* Variables and functions */
 size_t mark_for_codepoint (size_t) ; 
 char const** name_map ; 

__attribute__((used)) static inline const char* name_for_codepoint(char_type cp) {
	char_type m = mark_for_codepoint(cp); if (m == 0) return NULL;
	return name_map[m];
}