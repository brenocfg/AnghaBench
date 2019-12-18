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
struct TYPE_3__ {int len; char* str; } ;
typedef  TYPE_1__ word_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD_BITS (int) ; 
 int MAX_TEXT_LEN ; 
 int /*<<< orphan*/  NotWordCharDict ; 
 int /*<<< orphan*/  NotWordDict ; 
 int /*<<< orphan*/  WordCharDict ; 
 int /*<<< orphan*/  WordDict ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int bswap_32 (unsigned int) ; 
 int char_code_lookup (int /*<<< orphan*/ *,unsigned int,int*) ; 
 TYPE_1__* word_code_lookup (int /*<<< orphan*/ *,unsigned int,int*) ; 

int unpack_message (char *buff, char *from, int packed_len) {
  char *wptr = buff, *rptr = from;
  int bits = packed_len * 8 - 1;
  int k = from[packed_len-1];

  assert (k);
  while (!(k & 1)) { k >>= 1; bits--; }

  unsigned t = bswap_32 (*((unsigned *) rptr));
  unsigned z = (((unsigned char) rptr[4]) << 1) + 1;
  rptr += 5;

#define	LOAD_BITS(__n)	{ int n=(__n); bits-=n; do {if (!(z&0xff)) {z=((*rptr++)<<1)+1;} t<<=1; if (z&0x100) t++; z<<=1;} while (--n);}

  while (bits > 0) {
    word_t *W;
    int c, N, l;

    /* decode one word */
    W = word_code_lookup (&WordDict, t, &l);
    LOAD_BITS (l);
    if (W->len != 2 || W->str[0]) {
      char *p = W->str, *q = p + W->len;
      while (p < q) {
        *wptr++ = *p++;
      }
    } else {
      /* special case: word not in dictionary, decode N word characters */
      N = (unsigned char) W->str[1];
      assert (N > 0);
      do {
        c = char_code_lookup (&WordCharDict, t, &l);
        LOAD_BITS (l);
        *wptr++ = c;
      } while (--N);
    }

    if (bits <= 0) {
      break;
    }

    /* decode one not-word */
    W = word_code_lookup (&NotWordDict, t, &l);
    LOAD_BITS (l);
    if (W->len != 2 || W->str[0]) {
      char *p = W->str, *q = p + W->len;
      while (p < q) {
        *wptr++ = *p++;
      }
    } else {
      /* special case: not-word not in dictionary, decode N not-word characters */
      N = (unsigned char) W->str[1];
      assert (N > 0);
      do {
        c = char_code_lookup (&NotWordCharDict, t, &l);
        LOAD_BITS (l);
        *wptr++ = c;
      } while (--N);
    }
  }
  assert (!bits && wptr < buff + MAX_TEXT_LEN);

#undef LOAD_BITS

  *wptr = 0;

  return wptr - buff;
}