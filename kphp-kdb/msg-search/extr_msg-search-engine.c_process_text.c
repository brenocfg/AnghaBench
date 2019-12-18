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
typedef  scalar_t__ hash_t ;

/* Variables and functions */
 int MAX_QUERY_WORDS ; 
 int MaxQw ; 
 scalar_t__* Q ; 
 int Qw ; 
 int* is_letter ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,unsigned char*) ; 

int process_text (char *text) {
  //fprintf (stderr, "%d %d %s\n", msg_id, order, text);

  Qw = 0;

  while (is_letter[(unsigned char)*text] == 32) text++;

  while (*text) {
    char *sav = text;
    int i;
    union {
      unsigned char data[16];
      hash_t hash;
    } md5_h;

    for (;is_letter[(unsigned char)*text] > 32;++text) *text = is_letter[(unsigned char)*text];

    md5 ((unsigned char *) sav, text - sav, md5_h.data);

    for (;is_letter[(unsigned char)*text] == 32; ++text);

    if (MaxQw <= MAX_QUERY_WORDS) {
      for (i = 0; i < Qw; i++) {
	if (Q[i] == md5_h.hash) {
	  break;
	}
      }
      if (i < Qw) continue;
    }

    if (Qw == MaxQw) {
      return -1;
    }
    Q[Qw++] = md5_h.hash;

    //fprintf (stderr, "%llu\n", md5_h.hash);

  }

  return Qw;
}