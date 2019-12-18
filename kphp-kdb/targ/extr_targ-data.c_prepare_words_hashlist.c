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
typedef  int hash_t ;

/* Variables and functions */
 int* HL ; 
 int Hc ; 
 int MAX_WORD_HASHES ; 
 int MAX_WORD_LEN ; 
 char* Word ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int get_notword (char const*) ; 
 int get_word (char const*) ; 
 int /*<<< orphan*/  hsort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lc_str (char*,char const*,int) ; 
 int my_lc_str (char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  translit_str (char*,int,char*,int) ; 
 int verbosity ; 
 int word_crc64 (char*,int) ; 

int prepare_words_hashlist (const char *str, int flags, int pattern, int translit, int type) {
  int len;
  static char trans_buff[256];
  if (!flags) {
    Hc = 0;
  }
  if (str) {
    while (*str) {
      len = get_notword (str);
      if (len < 0) {
        break;
      }
      for (; len > 0; len--) {
        if (*str++ == 9) {
          pattern >>= 1;
        }
      }
      len = get_word (str);
      if (len < 0 || Hc >= MAX_WORD_HASHES) { break; }
      if (!len) {
        continue;
      }
      if (len < MAX_WORD_LEN && (pattern & 1)) {
	int len2 = len;
	if (translit) {
	  lc_str (Word, str, len);
	} else {
	  len2 = my_lc_str (Word, str, len);
	}
	HL[Hc++] = (word_crc64 (Word, len2) + type) | (1ULL << 63);
	if (translit && Hc < MAX_WORD_HASHES) {
	  translit_str (trans_buff, 250, Word, len);
	  if (strcmp (trans_buff, Word)) {
	    HL[Hc++] = (word_crc64 (trans_buff, -1) + type) | (1ULL << 63);
	    if (verbosity > 4) {
	      fprintf (stderr, "translit: '%s' -> '%s'\n", Word, trans_buff);
	    }
	  }
	}
      }
      str += len;
    }
  }
  if (flags <= 0 && Hc > 0) {
    int i, j = 1;
    hash_t h;
    hsort (0, Hc-1);
    h = HL[0];
    for (i = 1; i < Hc; i++) {
      if (HL[i] != h) {
	HL[j++] = h = HL[i];
      }
    }
    Hc = j;
  }
  return Hc;
}