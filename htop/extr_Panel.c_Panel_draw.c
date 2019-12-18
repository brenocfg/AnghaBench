#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int scrollH; int y; int x; int h; int w; int scrollV; int needsRedraw; int selected; int selectionColor; int selectedLen; int oldSelected; int /*<<< orphan*/  items; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ Panel ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int* CRT_colors ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  Object_display (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t PANEL_HEADER_FOCUS ; 
 size_t PANEL_HEADER_UNFOCUS ; 
 size_t PANEL_SELECTION_UNFOCUS ; 
 size_t RESET_COLOR ; 
 int /*<<< orphan*/  RichString_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RichString_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RichString_printoffnVal (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  RichString_setAttr (int /*<<< orphan*/ *,int) ; 
 int RichString_sizeVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Vector_get (int /*<<< orphan*/ ,int) ; 
 int Vector_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attrset (int) ; 
 int /*<<< orphan*/  item ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvhline (int,int,char,int) ; 
 int /*<<< orphan*/  new ; 
 int /*<<< orphan*/  old ; 

void Panel_draw(Panel* this, bool focus) {
   assert (this != NULL);

   int size = Vector_size(this->items);
   int scrollH = this->scrollH;
   int y = this->y;
   int x = this->x;
   int h = this->h;

   int headerLen = RichString_sizeVal(this->header);
   if (headerLen > 0) {
      int attr = focus
               ? CRT_colors[PANEL_HEADER_FOCUS]
               : CRT_colors[PANEL_HEADER_UNFOCUS];
      attrset(attr);
      mvhline(y, x, ' ', this->w);
      if (scrollH < headerLen) {
         RichString_printoffnVal(this->header, y, x, scrollH,
            MIN(headerLen - scrollH, this->w));
      }
      attrset(CRT_colors[RESET_COLOR]);
      y++;
   }

   // ensure scroll area is on screen
   if (this->scrollV < 0) {
      this->scrollV = 0;
      this->needsRedraw = true;
   } else if (this->scrollV >= size) {
      this->scrollV = MAX(size - 1, 0);
      this->needsRedraw = true;
   }
   // ensure selection is on screen
   if (this->selected < this->scrollV) {
      this->scrollV = this->selected;
      this->needsRedraw = true;
   } else if (this->selected >= this->scrollV + h) {
      this->scrollV = this->selected - h + 1;
      this->needsRedraw = true;
   }

   int first = this->scrollV;
   int upTo = MIN(first + h, size);

   int selectionColor = focus
                 ? this->selectionColor
                 : CRT_colors[PANEL_SELECTION_UNFOCUS];

   if (this->needsRedraw) {
      int line = 0;
      for(int i = first; line < h && i < upTo; i++) {
         Object* itemObj = Vector_get(this->items, i);
         assert(itemObj); if(!itemObj) continue;
         RichString_begin(item);
         Object_display(itemObj, &item);
         int itemLen = RichString_sizeVal(item);
         int amt = MIN(itemLen - scrollH, this->w);
         bool selected = (i == this->selected);
         if (selected) {
            attrset(selectionColor);
            RichString_setAttr(&item, selectionColor);
            this->selectedLen = itemLen;
         }
         mvhline(y + line, x, ' ', this->w);
         if (amt > 0)
            RichString_printoffnVal(item, y + line, x, scrollH, amt);
         if (selected)
            attrset(CRT_colors[RESET_COLOR]);
         RichString_end(item);
         line++;
      }
      while (line < h) {
         mvhline(y + line, x, ' ', this->w);
         line++;
      }
      this->needsRedraw = false;

   } else {
      Object* oldObj = Vector_get(this->items, this->oldSelected);
      assert(oldObj);
      RichString_begin(old);
      Object_display(oldObj, &old);
      int oldLen = RichString_sizeVal(old);
      Object* newObj = Vector_get(this->items, this->selected);
      RichString_begin(new);
      Object_display(newObj, &new);
      int newLen = RichString_sizeVal(new);
      this->selectedLen = newLen;
      mvhline(y+ this->oldSelected - first, x+0, ' ', this->w);
      if (scrollH < oldLen)
         RichString_printoffnVal(old, y+this->oldSelected - first, x,
            scrollH, MIN(oldLen - scrollH, this->w));
      attrset(selectionColor);
      mvhline(y+this->selected - first, x+0, ' ', this->w);
      RichString_setAttr(&new, selectionColor);
      if (scrollH < newLen)
         RichString_printoffnVal(new, y+this->selected - first, x,
            scrollH, MIN(newLen - scrollH, this->w));
      attrset(CRT_colors[RESET_COLOR]);
      RichString_end(new);
      RichString_end(old);
   }
   this->oldSelected = this->selected;
   move(0, 0);
}