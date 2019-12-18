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
typedef  int UWORD ;
typedef  size_t UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t FONT_BANK ; 
 int FONT_BANK_OFFSET ; 
 int /*<<< orphan*/  SetBankedBkgData (size_t,size_t,int,int) ; 
 size_t TEXT_BUFFER_START ; 
 int /*<<< orphan*/  TRUE ; 
 int avatar_enabled ; 
 scalar_t__* bank_data_ptrs ; 
 int menu_enabled ; 
 int /*<<< orphan*/  set_win_tiles (int,int,int,int,size_t*) ; 
 size_t strlen (int*) ; 
 size_t text_count ; 
 scalar_t__ text_draw_speed ; 
 int /*<<< orphan*/  text_drawn ; 
 int* text_lines ; 
 int text_num_lines ; 
 int text_tile_count ; 
 int text_wait ; 
 int text_x ; 
 int text_y ; 
 scalar_t__ win_speed ; 

void UIDrawTextBufferChar()
{
  UBYTE letter;
  UBYTE i, text_remaining, word_len;
  UBYTE text_size = strlen(text_lines);
  UBYTE tile;
  UWORD ptr;

  if (text_wait > 0)
  {
    text_wait--;
    return;
  }

  if (text_count < text_size)
  {
    win_speed = text_draw_speed;
    text_drawn = FALSE;

    if (text_count == 0)
    {
      text_x = 0;
      text_y = 0;
    }

    letter = text_lines[text_count] - 32;

    // Clear tile data ready for text
    ptr = ((UWORD)bank_data_ptrs[FONT_BANK]) + FONT_BANK_OFFSET;

    // Determine if text can fit on line
    text_remaining = 18 - text_x;
    word_len = 0;
    for (i = text_count; i != text_size; i++)
    {
      if (text_lines[i] == ' ' || text_lines[i] == '\n' || text_lines[i] == '\0')
      {
        break;
      }
      word_len++;
    }
    if (word_len > text_remaining && word_len < 18)
    {
      text_x = 0;
      text_y++;
    }

    if (text_lines[text_count] != '\b' && text_lines[text_count] != '\n')
    {
      i = text_tile_count + avatar_enabled * 4;
      SetBankedBkgData(FONT_BANK, TEXT_BUFFER_START + i, 1, ptr + ((UWORD)letter * 16));
      tile = TEXT_BUFFER_START + i;
      set_win_tiles(text_x + 1 + avatar_enabled * 2 + menu_enabled + (text_y >= text_num_lines ? 9 : 0), (text_y % text_num_lines) + 1, 1, 1, &tile);
      text_tile_count++;
    }

    if (text_lines[text_count] == '\b')
    {
      text_x--;
      text_wait = 10;
    }

    text_count++;
    text_x++;
    if (text_lines[text_count] == '\n')
    {
      text_x = 0;
      text_y++;
      text_count++;
    }
    else if (text_x > 17)
    {
      text_x = 0;
      text_y++;
    }

    if (text_draw_speed == 0)
    {
      UIDrawTextBufferChar();
    }
  }
  else
  {
    text_drawn = TRUE;
  }
}