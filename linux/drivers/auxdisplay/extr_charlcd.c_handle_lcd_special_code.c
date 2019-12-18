#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; int /*<<< orphan*/  y; } ;
struct TYPE_4__ {char* buf; int /*<<< orphan*/  len; } ;
struct charlcd_priv {int flags; TYPE_2__ addr; TYPE_1__ esc_seq; } ;
struct charlcd {int bwidth; int width; int ifwidth; TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* write_cmd ) (struct charlcd*,int) ;int /*<<< orphan*/  (* write_data ) (struct charlcd*,unsigned char) ;} ;

/* Variables and functions */
 int LCD_CMD_BLINK_ON ; 
 int LCD_CMD_CURSOR_ON ; 
 int LCD_CMD_DATA_LEN_8BITS ; 
 int LCD_CMD_DISPLAY_CTRL ; 
 int LCD_CMD_DISPLAY_ON ; 
 int LCD_CMD_DISPLAY_SHIFT ; 
 int LCD_CMD_FONT_5X10_DOTS ; 
 int LCD_CMD_FUNCTION_SET ; 
 unsigned char LCD_CMD_SET_CGRAM_ADDR ; 
 int LCD_CMD_SHIFT ; 
 int LCD_CMD_SHIFT_RIGHT ; 
 int LCD_CMD_TWO_LINES ; 
 int LCD_FLAG_B ; 
 int LCD_FLAG_C ; 
 int LCD_FLAG_D ; 
 int LCD_FLAG_F ; 
 int LCD_FLAG_L ; 
 int LCD_FLAG_N ; 
 int /*<<< orphan*/  charlcd_backlight (struct charlcd*,int) ; 
 int /*<<< orphan*/  charlcd_gotoxy (struct charlcd*) ; 
 int /*<<< orphan*/  charlcd_init_display (struct charlcd*) ; 
 int /*<<< orphan*/  charlcd_poke (struct charlcd*) ; 
 struct charlcd_priv* charlcd_to_priv (struct charlcd*) ; 
 int /*<<< orphan*/  parse_xy (char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  stub1 (struct charlcd*,int) ; 
 int /*<<< orphan*/  stub2 (struct charlcd*,int) ; 
 int /*<<< orphan*/  stub3 (struct charlcd*,int) ; 
 int /*<<< orphan*/  stub4 (struct charlcd*,int) ; 
 int /*<<< orphan*/  stub5 (struct charlcd*,char) ; 
 int /*<<< orphan*/  stub6 (struct charlcd*,unsigned char) ; 
 int /*<<< orphan*/  stub7 (struct charlcd*,unsigned char) ; 
 int /*<<< orphan*/  stub8 (struct charlcd*,int) ; 
 int /*<<< orphan*/  stub9 (struct charlcd*,int) ; 

__attribute__((used)) static inline int handle_lcd_special_code(struct charlcd *lcd)
{
	struct charlcd_priv *priv = charlcd_to_priv(lcd);

	/* LCD special codes */

	int processed = 0;

	char *esc = priv->esc_seq.buf + 2;
	int oldflags = priv->flags;

	/* check for display mode flags */
	switch (*esc) {
	case 'D':	/* Display ON */
		priv->flags |= LCD_FLAG_D;
		processed = 1;
		break;
	case 'd':	/* Display OFF */
		priv->flags &= ~LCD_FLAG_D;
		processed = 1;
		break;
	case 'C':	/* Cursor ON */
		priv->flags |= LCD_FLAG_C;
		processed = 1;
		break;
	case 'c':	/* Cursor OFF */
		priv->flags &= ~LCD_FLAG_C;
		processed = 1;
		break;
	case 'B':	/* Blink ON */
		priv->flags |= LCD_FLAG_B;
		processed = 1;
		break;
	case 'b':	/* Blink OFF */
		priv->flags &= ~LCD_FLAG_B;
		processed = 1;
		break;
	case '+':	/* Back light ON */
		priv->flags |= LCD_FLAG_L;
		processed = 1;
		break;
	case '-':	/* Back light OFF */
		priv->flags &= ~LCD_FLAG_L;
		processed = 1;
		break;
	case '*':	/* Flash back light */
		charlcd_poke(lcd);
		processed = 1;
		break;
	case 'f':	/* Small Font */
		priv->flags &= ~LCD_FLAG_F;
		processed = 1;
		break;
	case 'F':	/* Large Font */
		priv->flags |= LCD_FLAG_F;
		processed = 1;
		break;
	case 'n':	/* One Line */
		priv->flags &= ~LCD_FLAG_N;
		processed = 1;
		break;
	case 'N':	/* Two Lines */
		priv->flags |= LCD_FLAG_N;
		processed = 1;
		break;
	case 'l':	/* Shift Cursor Left */
		if (priv->addr.x > 0) {
			/* back one char if not at end of line */
			if (priv->addr.x < lcd->bwidth)
				lcd->ops->write_cmd(lcd, LCD_CMD_SHIFT);
			priv->addr.x--;
		}
		processed = 1;
		break;
	case 'r':	/* shift cursor right */
		if (priv->addr.x < lcd->width) {
			/* allow the cursor to pass the end of the line */
			if (priv->addr.x < (lcd->bwidth - 1))
				lcd->ops->write_cmd(lcd,
					LCD_CMD_SHIFT | LCD_CMD_SHIFT_RIGHT);
			priv->addr.x++;
		}
		processed = 1;
		break;
	case 'L':	/* shift display left */
		lcd->ops->write_cmd(lcd, LCD_CMD_SHIFT | LCD_CMD_DISPLAY_SHIFT);
		processed = 1;
		break;
	case 'R':	/* shift display right */
		lcd->ops->write_cmd(lcd,
				    LCD_CMD_SHIFT | LCD_CMD_DISPLAY_SHIFT |
				    LCD_CMD_SHIFT_RIGHT);
		processed = 1;
		break;
	case 'k': {	/* kill end of line */
		int x;

		for (x = priv->addr.x; x < lcd->bwidth; x++)
			lcd->ops->write_data(lcd, ' ');

		/* restore cursor position */
		charlcd_gotoxy(lcd);
		processed = 1;
		break;
	}
	case 'I':	/* reinitialize display */
		charlcd_init_display(lcd);
		processed = 1;
		break;
	case 'G': {
		/* Generator : LGcxxxxx...xx; must have <c> between '0'
		 * and '7', representing the numerical ASCII code of the
		 * redefined character, and <xx...xx> a sequence of 16
		 * hex digits representing 8 bytes for each character.
		 * Most LCDs will only use 5 lower bits of the 7 first
		 * bytes.
		 */

		unsigned char cgbytes[8];
		unsigned char cgaddr;
		int cgoffset;
		int shift;
		char value;
		int addr;

		if (!strchr(esc, ';'))
			break;

		esc++;

		cgaddr = *(esc++) - '0';
		if (cgaddr > 7) {
			processed = 1;
			break;
		}

		cgoffset = 0;
		shift = 0;
		value = 0;
		while (*esc && cgoffset < 8) {
			shift ^= 4;
			if (*esc >= '0' && *esc <= '9') {
				value |= (*esc - '0') << shift;
			} else if (*esc >= 'A' && *esc <= 'F') {
				value |= (*esc - 'A' + 10) << shift;
			} else if (*esc >= 'a' && *esc <= 'f') {
				value |= (*esc - 'a' + 10) << shift;
			} else {
				esc++;
				continue;
			}

			if (shift == 0) {
				cgbytes[cgoffset++] = value;
				value = 0;
			}

			esc++;
		}

		lcd->ops->write_cmd(lcd, LCD_CMD_SET_CGRAM_ADDR | (cgaddr * 8));
		for (addr = 0; addr < cgoffset; addr++)
			lcd->ops->write_data(lcd, cgbytes[addr]);

		/* ensures that we stop writing to CGRAM */
		charlcd_gotoxy(lcd);
		processed = 1;
		break;
	}
	case 'x':	/* gotoxy : LxXXX[yYYY]; */
	case 'y':	/* gotoxy : LyYYY[xXXX]; */
		if (priv->esc_seq.buf[priv->esc_seq.len - 1] != ';')
			break;

		/* If the command is valid, move to the new address */
		if (parse_xy(esc, &priv->addr.x, &priv->addr.y))
			charlcd_gotoxy(lcd);

		/* Regardless of its validity, mark as processed */
		processed = 1;
		break;
	}

	/* TODO: This indent party here got ugly, clean it! */
	/* Check whether one flag was changed */
	if (oldflags == priv->flags)
		return processed;

	/* check whether one of B,C,D flags were changed */
	if ((oldflags ^ priv->flags) &
	    (LCD_FLAG_B | LCD_FLAG_C | LCD_FLAG_D))
		/* set display mode */
		lcd->ops->write_cmd(lcd,
			LCD_CMD_DISPLAY_CTRL |
			((priv->flags & LCD_FLAG_D) ? LCD_CMD_DISPLAY_ON : 0) |
			((priv->flags & LCD_FLAG_C) ? LCD_CMD_CURSOR_ON : 0) |
			((priv->flags & LCD_FLAG_B) ? LCD_CMD_BLINK_ON : 0));
	/* check whether one of F,N flags was changed */
	else if ((oldflags ^ priv->flags) & (LCD_FLAG_F | LCD_FLAG_N))
		lcd->ops->write_cmd(lcd,
			LCD_CMD_FUNCTION_SET |
			((lcd->ifwidth == 8) ? LCD_CMD_DATA_LEN_8BITS : 0) |
			((priv->flags & LCD_FLAG_F) ? LCD_CMD_FONT_5X10_DOTS : 0) |
			((priv->flags & LCD_FLAG_N) ? LCD_CMD_TWO_LINES : 0));
	/* check whether L flag was changed */
	else if ((oldflags ^ priv->flags) & LCD_FLAG_L)
		charlcd_backlight(lcd, !!(priv->flags & LCD_FLAG_L));

	return processed;
}