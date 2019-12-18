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
 int EDIT_KEY_END ; 
 int EDIT_KEY_F1 ; 
 int EDIT_KEY_F2 ; 
 int EDIT_KEY_F3 ; 
 int EDIT_KEY_F4 ; 
 int EDIT_KEY_HOME ; 
 int EDIT_KEY_NONE ; 

__attribute__((used)) static enum edit_key_code esc_seq_to_key2(int param1, int param2, char last)
{
	/* ESC-O<param1>;<param2><last> */

	if (param1 >= 0 || param2 >= 0)
		return EDIT_KEY_NONE;

	switch (last) {
	case 'F':
		return EDIT_KEY_END;
	case 'H':
		return EDIT_KEY_HOME;
	case 'P':
		return EDIT_KEY_F1;
	case 'Q':
		return EDIT_KEY_F2;
	case 'R':
		return EDIT_KEY_F3;
	case 'S':
		return EDIT_KEY_F4;
	default:
		return EDIT_KEY_NONE;
	}
}