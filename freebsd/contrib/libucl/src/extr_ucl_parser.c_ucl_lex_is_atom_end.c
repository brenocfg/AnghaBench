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

/* Variables and functions */
 int /*<<< orphan*/  UCL_CHARACTER_VALUE_END ; 
 int ucl_test_character (unsigned char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
ucl_lex_is_atom_end (const unsigned char c)
{
	return ucl_test_character (c, UCL_CHARACTER_VALUE_END);
}