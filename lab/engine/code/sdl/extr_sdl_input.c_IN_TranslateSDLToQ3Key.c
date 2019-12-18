#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int keyNum_t ;
struct TYPE_6__ {scalar_t__ integer; } ;
struct TYPE_5__ {scalar_t__ scancode; int sym; } ;
typedef  TYPE_1__ SDL_Keysym ;

/* Variables and functions */
 scalar_t__ IN_IsConsoleKey (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_PrintKey (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int K_ALT ; 
 int K_BACKSPACE ; 
 int K_CAPSLOCK ; 
 int K_COMMAND ; 
 int K_CONSOLE ; 
 int K_CTRL ; 
 int K_DEL ; 
 int K_DOWNARROW ; 
 int K_END ; 
 int K_ENTER ; 
 int K_ESCAPE ; 
 int K_F1 ; 
 int K_F10 ; 
 int K_F11 ; 
 int K_F12 ; 
 int K_F13 ; 
 int K_F14 ; 
 int K_F15 ; 
 int K_F2 ; 
 int K_F3 ; 
 int K_F4 ; 
 int K_F5 ; 
 int K_F6 ; 
 int K_F7 ; 
 int K_F8 ; 
 int K_F9 ; 
 int K_HELP ; 
 int K_HOME ; 
 int K_INS ; 
 int K_KP_5 ; 
 int K_KP_DEL ; 
 int K_KP_DOWNARROW ; 
 int K_KP_END ; 
 int K_KP_ENTER ; 
 int K_KP_HOME ; 
 int K_KP_INS ; 
 int K_KP_LEFTARROW ; 
 int K_KP_MINUS ; 
 int K_KP_NUMLOCK ; 
 int K_KP_PGDN ; 
 int K_KP_PGUP ; 
 int K_KP_PLUS ; 
 int K_KP_RIGHTARROW ; 
 int K_KP_SLASH ; 
 int K_KP_STAR ; 
 int K_KP_UPARROW ; 
 int K_LEFTARROW ; 
 int K_MENU ; 
 int K_MODE ; 
 int K_PAUSE ; 
 int K_PGDN ; 
 int K_PGUP ; 
 int K_POWER ; 
 int K_PRINT ; 
 int K_RIGHTARROW ; 
 int K_SCROLLOCK ; 
 int K_SHIFT ; 
 int K_SUPER ; 
 int K_SYSREQ ; 
 int K_TAB ; 
 int K_UNDO ; 
 int K_UPARROW ; 
 int /*<<< orphan*/  K_WORLD_0 ; 
#define  SDLK_APPLICATION 192 
#define  SDLK_BACKSPACE 191 
#define  SDLK_CAPSLOCK 190 
#define  SDLK_DELETE 189 
#define  SDLK_DOWN 188 
#define  SDLK_END 187 
#define  SDLK_ESCAPE 186 
#define  SDLK_F1 185 
#define  SDLK_F10 184 
#define  SDLK_F11 183 
#define  SDLK_F12 182 
#define  SDLK_F13 181 
#define  SDLK_F14 180 
#define  SDLK_F15 179 
#define  SDLK_F2 178 
#define  SDLK_F3 177 
#define  SDLK_F4 176 
#define  SDLK_F5 175 
#define  SDLK_F6 174 
#define  SDLK_F7 173 
#define  SDLK_F8 172 
#define  SDLK_F9 171 
#define  SDLK_HELP 170 
#define  SDLK_HOME 169 
#define  SDLK_INSERT 168 
#define  SDLK_KP_0 167 
#define  SDLK_KP_1 166 
#define  SDLK_KP_2 165 
#define  SDLK_KP_3 164 
#define  SDLK_KP_4 163 
#define  SDLK_KP_5 162 
#define  SDLK_KP_6 161 
#define  SDLK_KP_7 160 
#define  SDLK_KP_8 159 
#define  SDLK_KP_9 158 
#define  SDLK_KP_DIVIDE 157 
#define  SDLK_KP_ENTER 156 
#define  SDLK_KP_MINUS 155 
#define  SDLK_KP_MULTIPLY 154 
#define  SDLK_KP_PERIOD 153 
#define  SDLK_KP_PLUS 152 
#define  SDLK_LALT 151 
#define  SDLK_LCTRL 150 
#define  SDLK_LEFT 149 
#define  SDLK_LGUI 148 
#define  SDLK_LSHIFT 147 
#define  SDLK_MENU 146 
#define  SDLK_MODE 145 
#define  SDLK_NUMLOCKCLEAR 144 
#define  SDLK_PAGEDOWN 143 
#define  SDLK_PAGEUP 142 
#define  SDLK_PAUSE 141 
#define  SDLK_POWER 140 
#define  SDLK_PRINTSCREEN 139 
#define  SDLK_RALT 138 
#define  SDLK_RCTRL 137 
#define  SDLK_RETURN 136 
#define  SDLK_RGUI 135 
#define  SDLK_RIGHT 134 
#define  SDLK_RSHIFT 133 
 int SDLK_SCANCODE_MASK ; 
#define  SDLK_SCROLLLOCK 132 
 int SDLK_SPACE ; 
#define  SDLK_SYSREQ 131 
#define  SDLK_TAB 130 
#define  SDLK_UNDO 129 
#define  SDLK_UP 128 
 scalar_t__ SDL_SCANCODE_0 ; 
 scalar_t__ SDL_SCANCODE_1 ; 
 TYPE_2__* in_keyboardDebug ; 

__attribute__((used)) static keyNum_t IN_TranslateSDLToQ3Key( SDL_Keysym *keysym, qboolean down )
{
	keyNum_t key = 0;

	if( keysym->scancode >= SDL_SCANCODE_1 && keysym->scancode <= SDL_SCANCODE_0 )
	{
		// Always map the number keys as such even if they actually map
		// to other characters (eg, "1" is "&" on an AZERTY keyboard).
		// This is required for SDL before 2.0.6, except on Windows
		// which already had this behavior.
		if( keysym->scancode == SDL_SCANCODE_0 )
			key = '0';
		else
			key = '1' + keysym->scancode - SDL_SCANCODE_1;
	}
	else if( keysym->sym >= SDLK_SPACE && keysym->sym < SDLK_DELETE )
	{
		// These happen to match the ASCII chars
		key = (int)keysym->sym;
	}
	else
	{
		switch( keysym->sym )
		{
			case SDLK_PAGEUP:       key = K_PGUP;          break;
			case SDLK_KP_9:         key = K_KP_PGUP;       break;
			case SDLK_PAGEDOWN:     key = K_PGDN;          break;
			case SDLK_KP_3:         key = K_KP_PGDN;       break;
			case SDLK_KP_7:         key = K_KP_HOME;       break;
			case SDLK_HOME:         key = K_HOME;          break;
			case SDLK_KP_1:         key = K_KP_END;        break;
			case SDLK_END:          key = K_END;           break;
			case SDLK_KP_4:         key = K_KP_LEFTARROW;  break;
			case SDLK_LEFT:         key = K_LEFTARROW;     break;
			case SDLK_KP_6:         key = K_KP_RIGHTARROW; break;
			case SDLK_RIGHT:        key = K_RIGHTARROW;    break;
			case SDLK_KP_2:         key = K_KP_DOWNARROW;  break;
			case SDLK_DOWN:         key = K_DOWNARROW;     break;
			case SDLK_KP_8:         key = K_KP_UPARROW;    break;
			case SDLK_UP:           key = K_UPARROW;       break;
			case SDLK_ESCAPE:       key = K_ESCAPE;        break;
			case SDLK_KP_ENTER:     key = K_KP_ENTER;      break;
			case SDLK_RETURN:       key = K_ENTER;         break;
			case SDLK_TAB:          key = K_TAB;           break;
			case SDLK_F1:           key = K_F1;            break;
			case SDLK_F2:           key = K_F2;            break;
			case SDLK_F3:           key = K_F3;            break;
			case SDLK_F4:           key = K_F4;            break;
			case SDLK_F5:           key = K_F5;            break;
			case SDLK_F6:           key = K_F6;            break;
			case SDLK_F7:           key = K_F7;            break;
			case SDLK_F8:           key = K_F8;            break;
			case SDLK_F9:           key = K_F9;            break;
			case SDLK_F10:          key = K_F10;           break;
			case SDLK_F11:          key = K_F11;           break;
			case SDLK_F12:          key = K_F12;           break;
			case SDLK_F13:          key = K_F13;           break;
			case SDLK_F14:          key = K_F14;           break;
			case SDLK_F15:          key = K_F15;           break;

			case SDLK_BACKSPACE:    key = K_BACKSPACE;     break;
			case SDLK_KP_PERIOD:    key = K_KP_DEL;        break;
			case SDLK_DELETE:       key = K_DEL;           break;
			case SDLK_PAUSE:        key = K_PAUSE;         break;

			case SDLK_LSHIFT:
			case SDLK_RSHIFT:       key = K_SHIFT;         break;

			case SDLK_LCTRL:
			case SDLK_RCTRL:        key = K_CTRL;          break;

#ifdef __APPLE__
			case SDLK_RGUI:
			case SDLK_LGUI:         key = K_COMMAND;       break;
#else
			case SDLK_RGUI:
			case SDLK_LGUI:         key = K_SUPER;         break;
#endif

			case SDLK_RALT:
			case SDLK_LALT:         key = K_ALT;           break;

			case SDLK_KP_5:         key = K_KP_5;          break;
			case SDLK_INSERT:       key = K_INS;           break;
			case SDLK_KP_0:         key = K_KP_INS;        break;
			case SDLK_KP_MULTIPLY:  key = K_KP_STAR;       break;
			case SDLK_KP_PLUS:      key = K_KP_PLUS;       break;
			case SDLK_KP_MINUS:     key = K_KP_MINUS;      break;
			case SDLK_KP_DIVIDE:    key = K_KP_SLASH;      break;

			case SDLK_MODE:         key = K_MODE;          break;
			case SDLK_HELP:         key = K_HELP;          break;
			case SDLK_PRINTSCREEN:  key = K_PRINT;         break;
			case SDLK_SYSREQ:       key = K_SYSREQ;        break;
			case SDLK_MENU:         key = K_MENU;          break;
			case SDLK_APPLICATION:	key = K_MENU;          break;
			case SDLK_POWER:        key = K_POWER;         break;
			case SDLK_UNDO:         key = K_UNDO;          break;
			case SDLK_SCROLLLOCK:   key = K_SCROLLOCK;     break;
			case SDLK_NUMLOCKCLEAR: key = K_KP_NUMLOCK;    break;
			case SDLK_CAPSLOCK:     key = K_CAPSLOCK;      break;

			default:
				if( !( keysym->sym & SDLK_SCANCODE_MASK ) && keysym->scancode <= 95 )
				{
					// Map Unicode characters to 95 world keys using the key's scan code.
					// FIXME: There aren't enough world keys to cover all the scancodes.
					// Maybe create a map of scancode to quake key at start up and on
					// key map change; allocate world key numbers as needed similar
					// to SDL 1.2.
					key = K_WORLD_0 + (int)keysym->scancode;
				}
				break;
		}
	}

	if( in_keyboardDebug->integer )
		IN_PrintKey( keysym, key, down );

	if( IN_IsConsoleKey( key, 0 ) )
	{
		// Console keys can't be bound or generate characters
		key = K_CONSOLE;
	}

	return key;
}