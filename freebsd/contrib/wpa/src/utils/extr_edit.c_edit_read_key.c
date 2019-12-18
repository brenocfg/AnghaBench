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
 int EDIT_KEY_BACKSPACE ; 
 int EDIT_KEY_CTRL_A ; 
 int EDIT_KEY_CTRL_B ; 
 int EDIT_KEY_CTRL_D ; 
 int EDIT_KEY_CTRL_E ; 
 int EDIT_KEY_CTRL_F ; 
 int EDIT_KEY_CTRL_G ; 
 int EDIT_KEY_CTRL_H ; 
 int EDIT_KEY_CTRL_J ; 
 int EDIT_KEY_CTRL_K ; 
 int EDIT_KEY_CTRL_L ; 
 int EDIT_KEY_CTRL_N ; 
 int EDIT_KEY_CTRL_O ; 
 int EDIT_KEY_CTRL_P ; 
 int EDIT_KEY_CTRL_R ; 
 int EDIT_KEY_CTRL_T ; 
 int EDIT_KEY_CTRL_U ; 
 int EDIT_KEY_CTRL_V ; 
 int EDIT_KEY_CTRL_W ; 
 int EDIT_KEY_ENTER ; 
 int EDIT_KEY_EOF ; 
 int EDIT_KEY_NONE ; 
 int EDIT_KEY_TAB ; 
 int esc_seq_to_key (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  show_esc_buf (char*,int,int) ; 

__attribute__((used)) static enum edit_key_code edit_read_key(int sock)
{
	int c;
	unsigned char buf[1];
	int res;
	static int esc = -1;
	static char esc_buf[7];

	res = read(sock, buf, 1);
	if (res < 0)
		perror("read");
	if (res <= 0)
		return EDIT_KEY_EOF;

	c = buf[0];

	if (esc >= 0) {
		if (c == 27 /* ESC */) {
			esc = 0;
			return EDIT_KEY_NONE;
		}

		if (esc == 6) {
			show_esc_buf(esc_buf, c, 0);
			esc = -1;
		} else {
			esc_buf[esc++] = c;
			esc_buf[esc] = '\0';
		}
	}

	if (esc == 1) {
		if (esc_buf[0] != '[' && esc_buf[0] != 'O') {
			show_esc_buf(esc_buf, c, 1);
			esc = -1;
			return EDIT_KEY_NONE;
		} else
			return EDIT_KEY_NONE; /* Escape sequence continues */
	}

	if (esc > 1) {
		if ((c >= '0' && c <= '9') || c == ';')
			return EDIT_KEY_NONE; /* Escape sequence continues */

		if (c == '~' || (c >= 'A' && c <= 'Z')) {
			esc = -1;
			return esc_seq_to_key(esc_buf);
		}

		show_esc_buf(esc_buf, c, 2);
		esc = -1;
		return EDIT_KEY_NONE;
	}

	switch (c) {
	case 1:
		return EDIT_KEY_CTRL_A;
	case 2:
		return EDIT_KEY_CTRL_B;
	case 4:
		return EDIT_KEY_CTRL_D;
	case 5:
		return EDIT_KEY_CTRL_E;
	case 6:
		return EDIT_KEY_CTRL_F;
	case 7:
		return EDIT_KEY_CTRL_G;
	case 8:
		return EDIT_KEY_CTRL_H;
	case 9:
		return EDIT_KEY_TAB;
	case 10:
		return EDIT_KEY_CTRL_J;
	case 13: /* CR */
		return EDIT_KEY_ENTER;
	case 11:
		return EDIT_KEY_CTRL_K;
	case 12:
		return EDIT_KEY_CTRL_L;
	case 14:
		return EDIT_KEY_CTRL_N;
	case 15:
		return EDIT_KEY_CTRL_O;
	case 16:
		return EDIT_KEY_CTRL_P;
	case 18:
		return EDIT_KEY_CTRL_R;
	case 20:
		return EDIT_KEY_CTRL_T;
	case 21:
		return EDIT_KEY_CTRL_U;
	case 22:
		return EDIT_KEY_CTRL_V;
	case 23:
		return EDIT_KEY_CTRL_W;
	case 27: /* ESC */
		esc = 0;
		return EDIT_KEY_NONE;
	case 127:
		return EDIT_KEY_BACKSPACE;
	default:
		return c;
	}
}