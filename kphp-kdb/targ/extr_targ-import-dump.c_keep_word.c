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

/* Variables and functions */
 int MAX_CHARS ; 
 scalar_t__ MAX_TERMS ; 
 int* TL ; 
 int TS ; 
 scalar_t__ Tc ; 
 int Tw ; 
 int /*<<< orphan*/  flush_words () ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 

__attribute__((used)) static void keep_word (char *str, int len) {
  if (len < 2 || len >= 64) { return; }
  memcpy (Tw, str, len+1);
  TL[Tc++] = Tw;
  Tw += (len + 4) & -4;
  if (Tw >= TS + MAX_CHARS - 512 || Tc >= MAX_TERMS) {
    flush_words ();
  }
}