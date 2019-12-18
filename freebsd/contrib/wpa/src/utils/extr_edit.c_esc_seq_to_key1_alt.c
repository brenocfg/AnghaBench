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
typedef  enum edit_key_code { ____Placeholder_edit_key_code } edit_key_code ;

/* Variables and functions */
 int EDIT_KEY_ALT_DOWN ; 
 int EDIT_KEY_ALT_LEFT ; 
 int EDIT_KEY_ALT_RIGHT ; 
 int EDIT_KEY_ALT_UP ; 
 int EDIT_KEY_NONE ; 

__attribute__((used)) static enum edit_key_code esc_seq_to_key1_alt(char last)
{
	switch (last) {
	case 'A':
		return EDIT_KEY_ALT_UP;
	case 'B':
		return EDIT_KEY_ALT_DOWN;
	case 'C':
		return EDIT_KEY_ALT_RIGHT;
	case 'D':
		return EDIT_KEY_ALT_LEFT;
	default:
		return EDIT_KEY_NONE;
	}
}