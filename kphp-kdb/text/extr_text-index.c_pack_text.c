#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ freq; int /*<<< orphan*/  code_len; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ word_t ;
struct TYPE_9__ {int /*<<< orphan*/ * code_len; int /*<<< orphan*/ * code; } ;
struct TYPE_8__ {int /*<<< orphan*/ * code_len; int /*<<< orphan*/ * code; } ;

/* Variables and functions */
 int /*<<< orphan*/  Encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EncodeBit (int) ; 
 TYPE_6__ NotWordCharDict ; 
 TYPE_1__** NotWordFreqWords ; 
 int /*<<< orphan*/  NotWords ; 
 TYPE_4__ WordCharDict ; 
 TYPE_1__** WordFreqWords ; 
 int /*<<< orphan*/  Words ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_notword (char*) ; 
 int get_word (char*) ; 
 TYPE_1__* hash_get (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

int pack_text (char *dest, int max_packed_len, char *text, int text_len) {
  char *ptr, *wptr = dest, *wptr_e = dest + max_packed_len;
  int len, x, y = 1;
  word_t *w;
  //fprintf (stderr, "TEXT: %s\n", text);
#define EncodeBit(__b)  { if (y >= 0x100) { *wptr++ = (char) y; y = 1; } y <<= 1; y += __b; }
#define Encode(__c,__l) { int t=__l; int c=__c; while (t>0) { EncodeBit(c < 0); c<<=1; t--; } }

  ptr = text;
  while (*ptr) {
    assert (wptr <= wptr_e);
    len = get_word (ptr);
    assert (len >= 0);
    //    fprintf (stderr, "WORD: '%.*s'\n", len, ptr);
    w = hash_get (&Words, ptr, len, 0);

    if (w && w->freq > 0) {
      Encode (w->code, w->code_len);
      ptr += len;
    } else {
      w = WordFreqWords[len];
      Encode (w->code, w->code_len);
      while (len > 0) {
        x = (unsigned char) *ptr++;
        Encode (WordCharDict.code[x], WordCharDict.code_len[x]);
        len--;
      }
    }

    if (!*ptr) {
      break;
    }

    len = get_notword(ptr);
    if (len < 0) {
      break;
    }
    //    fprintf (stderr, "NOT-WORD: '%.*s'\n", len, ptr);
    w = hash_get (&NotWords, ptr, len, 0);

    if (w && w->freq > 0) {
      Encode (w->code, w->code_len);
      ptr += len;
    } else {
      w = NotWordFreqWords[len];
      Encode (w->code, w->code_len);
      while (len > 0) {
        x = (unsigned char) *ptr++;
        Encode (NotWordCharDict.code[x], NotWordCharDict.code_len[x]);
        len--;
      }
    }
  }

  EncodeBit (1);
  while (y < 0x100) {
    EncodeBit (0);
  }
  *wptr++ = (char) y;
  assert (wptr <= wptr_e);
  return wptr - dest;

#undef EncodeBit
#undef Encode
}