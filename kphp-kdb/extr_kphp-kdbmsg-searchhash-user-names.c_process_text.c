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
struct TYPE_3__ {long user_id; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ userpair_t ;
typedef  int /*<<< orphan*/  hash_t ;
typedef  int /*<<< orphan*/  Tmp ;

/* Variables and functions */
 int* is_letter ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,unsigned char*) ; 
 int /*<<< orphan*/  tot_Pc ; 
 int /*<<< orphan*/  writeout (TYPE_1__*,int) ; 

void process_text (char *text, long user_id) {
  //fprintf (stderr, "%ld %s\n", user_id, text);
  while (is_letter[(unsigned char)*text] == 32) text++;

  while (*text) {
    char *sav = text;
    union {
      unsigned char data[16];
      hash_t hash;
    } md5_h;
    static userpair_t Tmp;

    for (;is_letter[(unsigned char)*text] > 32;++text) *text = is_letter[(unsigned char)*text];

    md5 ((unsigned char *) sav, text - sav, md5_h.data);

    Tmp.hash = md5_h.hash;
    Tmp.user_id = user_id;

    //fprintf (stderr, "%llu %d %d\n", P[Pc].hash, P[Pc].order, P[Pc].message_id);

    writeout (&Tmp, sizeof(Tmp));
    tot_Pc++;

    for (;is_letter[(unsigned char)*text] == 32; ++text);
  }
}