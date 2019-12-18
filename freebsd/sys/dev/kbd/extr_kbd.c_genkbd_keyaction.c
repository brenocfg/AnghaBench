#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct keyent_t {int flgs; int* map; int spcl; } ;
struct TYPE_8__ {int* kb_lastact; TYPE_1__* kb_keymap; } ;
typedef  TYPE_2__ keyboard_t ;
struct TYPE_7__ {struct keyent_t* key; } ;

/* Variables and functions */
 int AGRS ; 
 int AGRS1 ; 
 int AGRS2 ; 
#define  ALK 159 
 int ALKDOWN ; 
 int ALKED ; 
 scalar_t__ ALTGR_OFFSET ; 
 int ALTS ; 
 int ALTS1 ; 
 int ALTS2 ; 
#define  ASH 158 
 int BKEY ; 
#define  BTAB 157 
#define  CLK 156 
 int CLKDOWN ; 
 int CLKED ; 
 int CTLS ; 
 int CTLS1 ; 
 int CTLS2 ; 
#define  DBG 155 
#define  ERRKEY 154 
 int FKEY ; 
 int FLAG_LOCK_C ; 
 int FLAG_LOCK_N ; 
 int F_ACC ; 
 int F_FN ; 
#define  HALT 153 
#define  LALT 152 
#define  LALTA 151 
#define  LCTR 150 
#define  LCTRA 149 
#define  LSH 148 
#define  LSHA 147 
 int L_ACC ; 
 int L_FN ; 
#define  META 146 
 int METAS ; 
 int METAS1 ; 
 int MKEY ; 
#define  NEXT 145 
#define  NLK 144 
 int NLKDOWN ; 
 int NLKED ; 
#define  NOKEY 143 
#define  NOP 142 
#define  PDWN 141 
#define  PNC 140 
#define  PREV 139 
#define  RALT 138 
#define  RALTA 137 
#define  RBT 136 
#define  RCTR 135 
#define  RCTRA 134 
 int RELKEY ; 
#define  RSH 133 
#define  RSHA 132 
 int SHIFTAON ; 
 int SHIFTS ; 
 int SHIFTS1 ; 
 int SHIFTS2 ; 
#define  SLK 131 
 int SLKDOWN ; 
 int SPCLKEY ; 
#define  SPSC 130 
#define  STBY 129 
#define  SUSP 128 
 int make_accent_char (TYPE_2__*,int,int*) ; 
 int save_accent_key (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  set_lockkey_state (TYPE_2__*,int,int const) ; 

int
genkbd_keyaction(keyboard_t *kbd, int keycode, int up, int *shiftstate,
		 int *accents)
{
	struct keyent_t *key;
	int state = *shiftstate;
	int action;
	int f;
	int i;

	i = keycode;
	f = state & (AGRS | ALKED);
	if ((f == AGRS1) || (f == AGRS2) || (f == ALKED))
		i += ALTGR_OFFSET;
	key = &kbd->kb_keymap->key[i];
	i = ((state & SHIFTS) ? 1 : 0)
	    | ((state & CTLS) ? 2 : 0)
	    | ((state & ALTS) ? 4 : 0);
	if (((key->flgs & FLAG_LOCK_C) && (state & CLKED))
		|| ((key->flgs & FLAG_LOCK_N) && (state & NLKED)) )
		i ^= 1;

	if (up) {	/* break: key released */
		action = kbd->kb_lastact[keycode];
		kbd->kb_lastact[keycode] = NOP;
		switch (action) {
		case LSHA:
			if (state & SHIFTAON) {
				set_lockkey_state(kbd, state, ALK);
				state &= ~ALKDOWN;
			}
			action = LSH;
			/* FALL THROUGH */
		case LSH:
			state &= ~SHIFTS1;
			break;
		case RSHA:
			if (state & SHIFTAON) {
				set_lockkey_state(kbd, state, ALK);
				state &= ~ALKDOWN;
			}
			action = RSH;
			/* FALL THROUGH */
		case RSH:
			state &= ~SHIFTS2;
			break;
		case LCTRA:
			if (state & SHIFTAON) {
				set_lockkey_state(kbd, state, ALK);
				state &= ~ALKDOWN;
			}
			action = LCTR;
			/* FALL THROUGH */
		case LCTR:
			state &= ~CTLS1;
			break;
		case RCTRA:
			if (state & SHIFTAON) {
				set_lockkey_state(kbd, state, ALK);
				state &= ~ALKDOWN;
			}
			action = RCTR;
			/* FALL THROUGH */
		case RCTR:
			state &= ~CTLS2;
			break;
		case LALTA:
			if (state & SHIFTAON) {
				set_lockkey_state(kbd, state, ALK);
				state &= ~ALKDOWN;
			}
			action = LALT;
			/* FALL THROUGH */
		case LALT:
			state &= ~ALTS1;
			break;
		case RALTA:
			if (state & SHIFTAON) {
				set_lockkey_state(kbd, state, ALK);
				state &= ~ALKDOWN;
			}
			action = RALT;
			/* FALL THROUGH */
		case RALT:
			state &= ~ALTS2;
			break;
		case ASH:
			state &= ~AGRS1;
			break;
		case META:
			state &= ~METAS1;
			break;
		case NLK:
			state &= ~NLKDOWN;
			break;
		case CLK:
			state &= ~CLKDOWN;
			break;
		case SLK:
			state &= ~SLKDOWN;
			break;
		case ALK:
			state &= ~ALKDOWN;
			break;
		case NOP:
			/* release events of regular keys are not reported */
			*shiftstate &= ~SHIFTAON;
			return (NOKEY);
		}
		*shiftstate = state & ~SHIFTAON;
		return (SPCLKEY | RELKEY | action);
	} else {	/* make: key pressed */
		action = key->map[i];
		state &= ~SHIFTAON;
		if (key->spcl & (0x80 >> i)) {
			/* special keys */
			if (kbd->kb_lastact[keycode] == NOP)
				kbd->kb_lastact[keycode] = action;
			if (kbd->kb_lastact[keycode] != action)
				action = NOP;
			switch (action) {
			/* LOCKING KEYS */
			case NLK:
				set_lockkey_state(kbd, state, NLK);
				break;
			case CLK:
				set_lockkey_state(kbd, state, CLK);
				break;
			case SLK:
				set_lockkey_state(kbd, state, SLK);
				break;
			case ALK:
				set_lockkey_state(kbd, state, ALK);
				break;
			/* NON-LOCKING KEYS */
			case SPSC: case RBT:  case SUSP: case STBY:
			case DBG:  case NEXT: case PREV: case PNC:
			case HALT: case PDWN:
				*accents = 0;
				break;
			case BTAB:
				*accents = 0;
				action |= BKEY;
				break;
			case LSHA:
				state |= SHIFTAON;
				action = LSH;
				/* FALL THROUGH */
			case LSH:
				state |= SHIFTS1;
				break;
			case RSHA:
				state |= SHIFTAON;
				action = RSH;
				/* FALL THROUGH */
			case RSH:
				state |= SHIFTS2;
				break;
			case LCTRA:
				state |= SHIFTAON;
				action = LCTR;
				/* FALL THROUGH */
			case LCTR:
				state |= CTLS1;
				break;
			case RCTRA:
				state |= SHIFTAON;
				action = RCTR;
				/* FALL THROUGH */
			case RCTR:
				state |= CTLS2;
				break;
			case LALTA:
				state |= SHIFTAON;
				action = LALT;
				/* FALL THROUGH */
			case LALT:
				state |= ALTS1;
				break;
			case RALTA:
				state |= SHIFTAON;
				action = RALT;
				/* FALL THROUGH */
			case RALT:
				state |= ALTS2;
				break;
			case ASH:
				state |= AGRS1;
				break;
			case META:
				state |= METAS1;
				break;
			case NOP:
				*shiftstate = state;
				return (NOKEY);
			default:
				/* is this an accent (dead) key? */
				*shiftstate = state;
				if (action >= F_ACC && action <= L_ACC) {
					action = save_accent_key(kbd, action,
								 accents);
					switch (action) {
					case NOKEY:
					case ERRKEY:
						return (action);
					default:
						if (state & METAS)
							return (action | MKEY);
						else
							return (action);
					}
					/* NOT REACHED */
				}
				/* other special keys */
				if (*accents > 0) {
					*accents = 0;
					return (ERRKEY);
				}
				if (action >= F_FN && action <= L_FN)
					action |= FKEY;
				/* XXX: return fkey string for the FKEY? */
				return (SPCLKEY | action);
			}
			*shiftstate = state;
			return (SPCLKEY | action);
		} else {
			/* regular keys */
			kbd->kb_lastact[keycode] = NOP;
			*shiftstate = state;
			if (*accents > 0) {
				/* make an accented char */
				action = make_accent_char(kbd, action, accents);
				if (action == ERRKEY)
					return (action);
			}
			if (state & METAS)
				action |= MKEY;
			return (action);
		}
	}
	/* NOT REACHED */
}