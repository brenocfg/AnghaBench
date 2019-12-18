#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_t ;
struct TYPE_2__ {int order; int message_id; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 size_t MAX_PAIRS ; 
 TYPE_1__* P ; 
 size_t Pc ; 
 int /*<<< orphan*/  assert (int) ; 
 int* is_letter ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,unsigned char*) ; 

void process_text (char *text, int msg_id, int order) {
  //fprintf (stderr, "%d %d %s\n", msg_id, order, text);

  if (text[0] == 'R' && text[1] == 'e' && text[2] < 'A') { text += 2; }

  while (is_letter[(unsigned char)*text] == 32) text++;

  while (*text) {
    char *sav = text;
    union {
      unsigned char data[16];
      hash_t hash;
    } md5_h;

    for (;is_letter[(unsigned char)*text] > 32;++text) *text = is_letter[(unsigned char)*text];

    md5 ((unsigned char *) sav, text - sav, md5_h.data);

    P[Pc].hash = md5_h.hash;
    P[Pc].order = order;
    P[Pc].message_id = msg_id;

    //fprintf (stderr, "%llu %d %d\n", P[Pc].hash, P[Pc].order, P[Pc].message_id);

    ++Pc;

    assert (Pc <= MAX_PAIRS);

    for (;is_letter[(unsigned char)*text] == 32; ++text);
  }
}