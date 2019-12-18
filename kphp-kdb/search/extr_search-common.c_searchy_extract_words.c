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
struct TYPE_3__ {int word; int freqs; } ;
typedef  TYPE_1__ pair_word_freqs_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int get_notword (char const*) ; 
 int get_word (char const*) ; 
 int /*<<< orphan*/  kprintf (char*,char const*) ; 
 int make_tag (char*,int,int) ; 
 void* searchy_term_hash (char*,int,int) ; 
 void* searchy_word_hash (char const*,int) ; 

int searchy_extract_words (const char *text, int len, int universal, pair_word_freqs_t *Q, int max_words, int tag_owner, long long item_id, int *positions) {
  int no_nw = 1;
  const char *prev = 0;
  int Qw = 0;
  *positions = 0;

  if (universal) {
    Q[Qw].word = searchy_word_hash ("\x1f@@", 3);
    Q[Qw].freqs = 0;
    Qw++;
  }

  if (tag_owner && ((int) (item_id >> 32))) {
    int owner_id = (int) item_id;
    if (owner_id) {
      Q[Qw].word = owner_id > 0 ? make_tag ("O", 1, owner_id) : make_tag ("W", 1, -owner_id);
      Q[Qw].word &= 0x7fffffffffffffffULL;
      Q[Qw].freqs = 0;
      Qw++;
    }
  }

  while (Qw < max_words && *text) {
    if (text == prev) {
      kprintf ("error at %.30s\n", text);
      exit (2);
    }
    prev = text - no_nw;
    int wl = no_nw ? 0 : get_notword (text);
    no_nw = 0;
    if (wl < 0) {
      break;
    }
    while (wl > 0 && *text != 0x1f) {
      text++;
      wl--;
    }
    if (*text == 0x1f) {
      wl = 1;
      while ((unsigned char) text[wl] >= 0x40) {
        wl++;
      }
      no_nw = 1;
    } else {
      wl = get_word (text);
    }
    if (!wl) {
      continue;
    }
    assert (wl > 0 && wl < 511);
    if (*text == 0x1f) {
      Q[Qw].word = searchy_word_hash (text, wl);
      Q[Qw++].freqs = 0; /* we don't count tags */
    } else {
      (*positions)++;
      Q[Qw].word = searchy_term_hash ((char *) text, wl, 0);
      Q[Qw++].freqs = *positions;
      if (!no_nw && Qw < max_words) {
        Q[Qw].word = searchy_term_hash ((char *) text, wl, 1);
        if (Q[Qw].word != Q[Qw-1].word) {
          Q[Qw++].freqs = *positions;
        }
      }
    }
    text += wl;
  }

  return Qw;
}