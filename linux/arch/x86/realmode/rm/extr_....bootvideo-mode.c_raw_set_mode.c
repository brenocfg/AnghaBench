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
typedef  int u16 ;
struct mode_info {int x; int y; int mode; } ;
struct card_info {int nmodes; int (* set_mode ) (struct mode_info*) ;int xmode_first; int xmode_n; struct mode_info* modes; } ;

/* Variables and functions */
 int VIDEO_RECALC ; 
 int stub1 (struct mode_info*) ; 
 int stub2 (struct mode_info*) ; 
 struct card_info* video_cards ; 
 struct card_info* video_cards_end ; 

__attribute__((used)) static int raw_set_mode(u16 mode, u16 *real_mode)
{
	int nmode, i;
	struct card_info *card;
	struct mode_info *mi;

	/* Drop the recalc bit if set */
	mode &= ~VIDEO_RECALC;

	/* Scan for mode based on fixed ID, position, or resolution */
	nmode = 0;
	for (card = video_cards; card < video_cards_end; card++) {
		mi = card->modes;
		for (i = 0; i < card->nmodes; i++, mi++) {
			int visible = mi->x || mi->y;

			if ((mode == nmode && visible) ||
			    mode == mi->mode ||
			    mode == (mi->y << 8)+mi->x) {
				*real_mode = mi->mode;
				return card->set_mode(mi);
			}

			if (visible)
				nmode++;
		}
	}

	/* Nothing found?  Is it an "exceptional" (unprobed) mode? */
	for (card = video_cards; card < video_cards_end; card++) {
		if (mode >= card->xmode_first &&
		    mode < card->xmode_first+card->xmode_n) {
			struct mode_info mix;
			*real_mode = mix.mode = mode;
			mix.x = mix.y = 0;
			return card->set_mode(&mix);
		}
	}

	/* Otherwise, failure... */
	return -1;
}